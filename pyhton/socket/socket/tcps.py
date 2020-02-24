import socket
import threading
import hashlib
import time


def tcps_rx_tx(conn, size=64):
    tx_size = 1
    while tx_size <= size:
        # rx_data_md5 = hashlib.md5()
        tx_data = '1' * tx_size
        rx_data = conn.recv(4096)
        conn.sendall(tx_data.encode())
        # rx_data.update(rx_data)
        # d_md5.hexdigest()
        print("tcps | rx: %d | %s | tx: %d | %s" % (len(rx_data), set(rx_data.decode('utf-8')), tx_size, set(tx_data)))
        tx_size += 1
    time.sleep(2)


HOST = '127.0.0.1'
PORT = 9999
listen_num = 20

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(listen_num)

while listen_num:
    conn, addr = s.accept()
    tcps_rx_tx(conn, 2000)
    listen_num -= 1
