#!/usr/bin/python

import socket
import hashlib
import threading

HOST = 'localhost'
PORT = 9999

data = ''
d_len = 0

def c_send1():
    '''method1: fill the buff with a file'''
    with open('test','rb') as f:
        data = f.read(20373504)
    d_md5 = hashlib.md5()
    d_md5.update(data)

    c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # c.settimeout(1)
    c.connect((HOST, PORT))

    while True:
        c.sendall(data)
        print "| c_send1: %d | %s |" % (len(data), d_md5.hexdigest())
        c.send('==End8==')

    c.close()

def c_send2(conn):
    '''method2: fill the buff with a special character'''
    t_data = '0' * 4096000
    total = 0
    while True:
        conn.sendall(t_data)
        total += len(t_data)
        #print "| c_send2: %d | %s |" % (len(t_data), ''.join(set(t_data)))


def c_recv2(conn):
    total = 0
    while True:
        r_data = conn.recv(4096)
        total += len(r_data)
        #print "| c_recv2: %d | %s |" % (len(r_data), ''.join(set(r_data)))

        if ('1' != ''.join(set(r_data))):
            print 'c_recv2 error occured @ %d' % total

        if(len(r_data)==0):
            break

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

t_thread = threading.Thread(target=c_send2,
                              name="c_send2",
                              args=(sock, ))
r_thread = threading.Thread(target=c_recv2,
                                name="c_recv2",
                                args=(sock,))
r_thread.daemon=True
t_thread.daemon = True
r_thread.start()
t_thread.start()
r_thread.join()




    



