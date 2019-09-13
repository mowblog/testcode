#!/usr/bin/env python3

from hexdump import hexdump
import binascii

def get_str_len(dest):
    str_len = len(dest)

    str_len = '{:x}'.format(str_len)
    if len(str_len) % 2 == 1:
        result = binascii.a2b_hex(str_len[0:(len(str_len))-1])
        result += binascii.a2b_hex('0' + str_len[(len(str_len))-1])
    else:
        result = binascii.a2b_hex(str_len)

    if len(result) <= 4:
        result = result.ljust(4,b'\x00')
    else:
        print("string length out of range")
    print(result)

get_str_len(b''.ljust(6559351,b'a'))

