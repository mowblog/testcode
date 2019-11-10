# -*- coding: utf-8 -*-

import socketserver
import socket

"""
测试环境：Ubuntu
Pyhton3.6.5
web访问: http://127.0.0.1:9999 通过
curl: curl http://127.0.0.1:9999 通过
"""


class myHandler(socketserver.BaseRequestHandler):
    def handle(self):
        # self.rdata = self.rfile.readline()
        self.rdata = self.request.recv(1024)
        print("recv: {}".format(self.rdata))
        # 测试for方法独到最后会持续阻塞
        # for item in self.rfile:
        #     print("{} write: {}".format(self.client_address[0], item))
        # self.function1()
        # self.wfile.write(b'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html>hello</html>')
        # self.wfile.write(b'got it')
        self.request.send(b'got it')

        print("send: {}".format(b'got it'))

    def function1(self):
        if 'GET' in self.rdata.decode('utf-8'):
            self.function2()

    def function2(self):
        """测试rfile中的数据可以缓存后续继续read"""
        while True:
            item = self.rfile.readline()
            # 此处无法设置非阻塞，通过判断http请求中最后一组数据为\r\n来退出循环
            if item == b"\r\n":
                break
            print("{} write: {}".format(self.client_address[0], item))


if __name__ == "__main__":
    # 全局设置端口重用
    socketserver.ThreadingTCPServer.allow_reuse_address = True

    server = socketserver.ThreadingTCPServer(('127.0.0.1', 9999), myHandler)
    # 设置端口重用
    # server.allow_reuse_address = True
    # 网上关于设置socket参数方法
    # server.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    # 设置非阻塞不生效
    # server.socket.setblocking(False)
    server.serve_forever()
