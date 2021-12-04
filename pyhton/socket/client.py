# Echo client program
import socket
import time,threading

local = ''
remote = '127.0.0.1'
port = 50007              # The same port as used by the server
name='client'
cwords=''

flag = 0 #1:tcp 0:udp
lock = threading.Lock()

'''
try:
    print('please input the remote server\'s addr:',end='')
    remote=input()
    print('please input the remote server\'s port:',end='')
    port=int(input())
    print('please input the your name:',end='')
    name=input()
except:
    print('please input right data')
    exit()
    '''


def client():
	udpc=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
	tcpc=socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	tcpc.connect((remote,port))
        
    def senddata():
        #global flag
        #global cwords
        while True:
            print(name + ':',end='')
            words=input()
            flag=1


    def recvdata():
        global flag
        global cwords
		#global tcpc
		#global udpc
        while True:
            if flag==1:
                udpc.sendto(bytearray(name + '(' + time.strftime('%Y-%m-%d %X',time.localtime(time.time())) + '):','utf-8'),(remote,port))
                tcpc.sendall(bytearray(cwords,'utf-8'))
                flag=0
            cdata1,caddr1=udpc.recvfrom(1024)
            cdata2 = tcpc.recv(1024)
            print(repr(cdata1) + ':' + repr(cdata2))
                
    sd=threading.Thread(target=senddata,name='senddata')
    rd=threading.Thread(target=recvdata,name='recvdata')
    sd.start()
    rd.start()
    #sd.join()
    #rd.join()

client()


