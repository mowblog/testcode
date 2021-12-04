import socket


tcps = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcps.bind(('192.168.1.5', 8888))
tcps.listen(1)

tconn,taddr=tcps.accept()
while(tconn):
    rdata=tconn.recv(1024)
    tconn.send(b'b'*10)
    print(rdata.decode('utf-8'))

