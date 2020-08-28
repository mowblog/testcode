# from __future__ import print_function
import sys
import clr
clr.AddReferenceByPartialName("Peach.Core")

import Peach.Core
# import Peach.Core.BitWise

import hashlib

password="Aa123456"

def hex_dump(data):
    print('len is :%d' % len(data))
    _str = [ord(i) for i in data]
    for i in _str:
        print hex(i),
    print("")

def xor(str1, str2):
    return ''.join(chr((ord(a)^ord(b))) for a,b in zip(str1,str2))

def get_datamodel(ctx, name):
    datamodel = ctx.dataModel.find(name)
    _str = ''
    # print(type(datamodel))
    while True:
        r = datamodel.Value.ReadByte()
        if r != -1:
            _str += chr(r)
        else:
            break
    return _str

def put_ctx_data(ctx):
    print(sys.version)
 
    # print(dir(ctx))
    # print(dir(ctx.parent))
    # print(dir(ctx.parent.parent))
    print(dir(ctx.parent.parent.parent.context))
    print(type(ctx.parent.parent.parent.context.stateStore))
    print(type(ctx.parent.parent.parent.context.iterationStateStore))
    ctx.parent.parent.parent.context.stateStore["k1"]="v1" 
    ctx.parent.parent.parent.context.iterationStateStore["k2"]="v2"

    # ctx.parent.parent.parent.dataModels.Insert("key1"="value1")
    # print(ctx.parent.parent.parent.dataModels)
    
    result = ctx.dataModel.find("test1")
    # print(dir(result))
    result.DefaultValue = Peach.Core.Variant(6)

def get_salt(ctx):
    salt1 = get_datamodel(ctx, "Salt1")
    salt2 = get_datamodel(ctx, "Salt2")
    salt = salt1 + salt2
    hex_dump(salt)
    ctx.parent.parent.parent.context.iterationStateStore["salt"] = salt

def set_password(ctx):
    salt = ctx.parent.parent.parent.context.iterationStateStore["salt"]
    secret = xor(hashlib.sha1(password).digest(), hashlib.sha1(salt + hashlib.sha1(hashlib.sha1(password).digest()).digest()).digest())
    print(len(secret))
    # hex_dump(secret)
    Password = ctx.dataModel.find("Password")
    if Password is None:
        return
    # print(help(Password.Value.Write))
    # a = Peach.Core.BitStream()
    # Password.DefaultValue = Peach.Core.Variant(bytes(secret, encoding = "utf8") )
    # Password.DefaultValue = Peach.Core.Variant(secret)
    for i in secret:
        Password.Value.WriteByte(ord(i))
    # Password.Value.Write(bytes(secret, encoding = "utf8"), 0, 20)
    # Password.DefaultValue = Peach.Core.Variant('\xff\xff')
    