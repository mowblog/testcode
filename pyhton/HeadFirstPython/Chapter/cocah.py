def formData(List):
    for each in List:
        if('-' in each):
            sep='-'
        elif(':' in each):
            sep=':'
        else:
            return each
        (m,s)=each.split(sep)
        return [m+'.'+s]

try:
    with open('sara.txt','r') as sara:
          sara_f=sara.readline()
    sara_s=[formData(t) for t in sara_f]

    print(sara_s)
except IOError as ior:
    print('operate file:' + str(ior))
