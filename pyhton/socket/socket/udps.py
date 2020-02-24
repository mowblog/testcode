import socket
import threading
import hashlib
import time


def udps_rx_tx(conn,size=64):
    tx_size = 1
    while tx_size <= size:
        #rx_data_md5 = hashlib.md5()
        tx_data = '1' * tx_size
        rx_data,addr = conn.recvfrom(4096)
        conn.sendto(tx_data.encode('utf-8'),addr)
        # rx_data.update(rx_data)
        # d_md5.hexdigest()
        print("udps | rx: %d | %s | tx: %d | %s" % (len(rx_data), set(rx_data.decode('utf-8')), tx_size, set(tx_data)))
        tx_size += 1



HOST = '127.0.0.1'
PORT = 9999
listen_num = 20

udps = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udps.bind((HOST, PORT))

udps_rx_tx(udps,2000)
