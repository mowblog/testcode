def str_2_hex(src):
    str=''
    for ch in src:
        str += format('%2x' % ord(ch))
    return str


t_str='this is a test string with \'Hello\''

t_str=str_2_hex(t_str)

if len(t_str)<100:
    t_str += (100-len(t_str))*'0'
print t_str

