import socket


tcpc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


while True:
    tconn=tcpc.connect_ex(('192.168.1.5',8888))
    if tconn==0:
        while True:
            try:
                tcpc.sendall(b'a'*10)
                print(tcpc.recv(1024))
                input()
            except:
                continue
    else:
        continue
