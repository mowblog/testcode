# Echo server program
import socket
import time
import threading

local = ''                 # Symbolic name meaning all available interfaces
port = 50007              # Arbitrary non-privileged port
name='server'


flag = 0 #1:tcp 0:udp
lock = threading.Lock()

'''
try:
    print('please input the port you want to use:',end='')
    port=int(input())
    print('please input your name:',end='')
    name=input()
except:
    print('please input right data')
    '''


def server():
	udps=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	tcps=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
   
	udps.bind((local,port))
	tcps.bind((local,port))
	tcps.listen(1)
	conn2, addr2 = tcps.accept()


	def recvdata():
		global flag
		global words
		while True:
			data1,addr1=udps.recvfrom(1024)
			data2 = conn2.recv(1024)
			print(repr(data1) + ':' + repr(data2))
			if flag==1:
				udps.sendto(bytearray(name + '(' + time.strftime('%Y-%m-%d %X',time.localtime(time.time())) + ')','utf-8'), addr1)
				conn2.sendall(bytearray(words,'utf-8'))
				flag=0
                
                
	def senddata():
		global flag
		global words
		while True:
			print(name + ':',end='')
			words=input()
			flag=1


	sd=threading.Thread(target=senddata,name='senddata')
	rd=threading.Thread(target=recvdata,name='recvdata')
	sd.start()
	rd.start()
	#sd.join()
	#rd.join()
		

    
server()



                   
                   
