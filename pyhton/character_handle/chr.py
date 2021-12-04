# -*- coding:utf-8 -*-
import sys

non_bmp_map = dict.fromkeys(range(0x10000, sys.maxunicode + 1), 0xfffd)
#print(x.translate(non_bmp_map))

for i in range(65534,0x10ffff):
    if(i<65535):
        print(format("%6X: %s") % (i, chr(i)) )

    else:
        print(format("%10X: %s") % (i, chr(i).translate(non_bmp_map)) )
        #print(ord(chr(i).translate(non_bmp_map)))
print('这是汉字')
print('这是汉字2'.encode('utf-8'))
print(b'\xe8\xbf\x99\xe6\x98\xaf\xe6\xb1\x89\xe5\xad\x972'.decode('utf-8'))
