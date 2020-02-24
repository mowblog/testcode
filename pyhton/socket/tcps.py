#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import threading
import hashlib

HOST = 'localhost'
PORT = 9999
l_flags = 20

'''接收t_num数量的包'''
def s_recv1(conn, num):
    d_len = 0
    r_data = ''
    
    while True :
        t_num = 4974
        d_md5 = hashlib.md5()
        while t_num:
            r_data += conn.recv(4096)
            t_num -= 1
            
        d_md5.update(r_data)
        print "| %s recv: %d | %s |" % (num, len(r_data), d_md5.hexdigest())

    #conn.shutdown(socket.SHUT_RDWR)
    conn.close()

'''标志判断==End==='''
def s_recv2(conn,num):
    while True:
        d_md5 = hashlib.md5()
        r_data = ''
        data = conn.recv(4096)
        r_data += data
        if '==End8==' in data:
            r_tmp = data[data.find('==End8==')+8:]
            r_data = r_data[0:r_data.find('==End8==')]
            #print r_data
            d_md5.update(r_data)
            #print "| %s recv: %d | %s |" % (num, len(r_data), d_md5.hexdigest())

def s_recv3(conn,num):
    total = 0
    while True:
        r_data = conn.recv(4096)
        total += len(r_data)
        #print "| %s s_recv3: %d | %s |" % (num, len(r_data), ''.join(set(r_data)))
        if('0' != ''.join(set(r_data) )):
            print 'error occured @ %d' % total

        if(len(r_data)==0):
            break


def s_send3(conn,num):
    t_data = '1' * 4096
    total = 0
    while True:
        conn.sendall(t_data)
        total += len(t_data)
        #print "| s_send3: %d | %s |" % (len(t_data), ''.join(set(t_data)))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST,PORT))
s.listen(l_flags)

while l_flags:
    conn,addr = s.accept()
    #conn.settimeout(1)
    #conn.setblocking(0)
    r_thread = threading.Thread(target=s_recv3,
                              name="s_recv3" + format('%d' % l_flags),
                              args=(conn, format('%d' % l_flags)))
    t_thread = threading.Thread(target=s_send3,
                                name="s_send3_" + format('%d' % l_flags),
                                args=(conn, format('%d' % l_flags)))
    r_thread.daemon=True
    t_thread.daemon = True
    r_thread.start()
    t_thread.start()

    l_flags -= 1



