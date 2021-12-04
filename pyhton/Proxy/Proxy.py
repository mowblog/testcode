# -*- coding: utf-8 -*-
import socket
import ssl
import threading
import queue
import time

fromCliQueue = queue.Queue()
fromSrvQueue = queue.Queue()

sFlag = False


class proxyClient(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.sock = None

    def run(self):
        global fromCliQueue
        global fromSrvQueue
        while True:
            if self.sock is None and not fromCliQueue.empty():
                self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
                self.sock.connect(('127.0.0.1', 8888))
            else:
                if not fromCliQueue.empty():
                    self.sock.send(fromCliQueue.get())
                    rdata = self.sock.recv(4096)
                    fromSrvQueue.put(rdata)




class proxyServer(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(('127.0.0.1',9999))
        self.sock.listen(1)


    def run(self):
        global fromSrvQueue
        global fromCliQueue
        self.proxySocket, addr = self.sock.accept()
        while self.proxySocket:
            rdata = self.proxySocket.recv(4096)
            fromCliQueue.put(rdata)
            while True:
                if fromSrvQueue.empty():
                    time.sleep(1)
                    continue
                else:
                    self.proxySocket.send(fromSrvQueue.get())
                    break;

if __name__ == "__main__":
    proxyCli = proxyClient()
    proxyCli.daemon = True
    proxyCli.start()

    proxySrv = proxyServer()
    proxySrv.daemon = True
    proxySrv.start()

    proxySrv.join()