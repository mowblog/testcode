#http://stackoverflow.com/questions/4213095/python-and-ctypes-how-to-correctly-pass-pointer-to-pointer-into-dll
from ctypes import *
from builtins import print, map

libc = windll.LoadLibrary("libpydll.dll")

pchar_pchar_t = libc.pchar_pchar_t
pchar_ppchar_t = libc.pchar_ppchar_t
result = -1

input = create_string_buffer(b"this is a sample")
print (input.value)
output = create_string_buffer(1024)

result = pchar_pchar_t(input,output)
if result == 0:
	print (output.value)
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
#			print(output2[i],end="")
#			output_s =output_s.join(str(output2[i]))
			output_s += output2[i].decode('utf-8')
	print(output_s)
#		else:
#			print (output2[i],end="")
#	print ("%s" % output2.contents.value)
