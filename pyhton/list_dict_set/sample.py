import pickle

tmpl=[1,2,3,4,5,6]
print(tmpl)

tmpl[0]=tmpl[1]+tmpl[2]
print(tmpl)

tmpl.append([8,'9'])
print(tmpl)

tmpl.insert(6,'7')
print(tmpl)

tmpl.append(10)
print(tmpl)

tmpl.pop()
print(tmpl)

tmpl3=tmpl
tmpl.pop(1)
print(tmpl)
print(tmpl3)

#tmps=set(tmpl)

with open('tmp.txt','wb+') as f:
	pickle.dump(tmpl,f)


with open('tmp.txt','rb+') as f:
        tmpl2=pickle.load(f)
        print(tmpl2)
        
