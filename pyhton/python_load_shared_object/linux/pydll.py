#http://stackoverflow.com/questions/4213095/python-and-ctypes-how-to-correctly-pass-pointer-to-pointer-into-dll
from ctypes import *

libc = cdll.LoadLibrary("libpydll.so")

pchar_pchar_t = libc.pchar_pchar_t
pchar_ppchar_t = libc.pchar_ppchar_t

input = create_string_buffer(b"this is a sample")
#print (input.value)
#input = "this is a sample!"
output = create_string_buffer(1024)

result = pchar_pchar_t(input,output)
if result == 0:
	print ("pchar_pchar_t output: %s" % output.value)
else:
	print ("pchar_pchar_t: failed")

output2 = POINTER(c_char)()
output_s = ""
result = pchar_ppchar_t(input, byref(output2))
if result != 0:
	print ("pchar_ppchar_t: failed")
else:
	for i in range(1024):
		if output2[i] != b'\000':
			output_s += output2[i].decode('utf-8')
	print("pchar_ppchar_t output: %s" % output_s)
