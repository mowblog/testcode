import math

'''
The sample Command:
ADD User: SerialNUmber=S'46002100000001,ID=I'00001;

Our purpose is to generate 300 similar commands as below:
ADD User: SerialNUmber=S'46002100000002,ID=I'00002;
ADD User: SerialNUmber=S'46002100000003,ID=I'00003;
'''

A1=46002100000001
B1=800001

fName="Command.txt"

try:
    fo=open(fName,"w+")
    for i in range(1,300):
        A1+=1
        B1+=1
        CMD="ADD User: SerialNUmber=S'"+str(A1) + ",ID=I'" + str(B1) + ";"
        print(CMD)
        fo.write(CMD + "\n")
    fo.close()   
except:
    print('Error occured,please check and run again...')
