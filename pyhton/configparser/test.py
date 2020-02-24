import configparser

#outputFile=open('ConfigSample_filter.ini','w+')
cf=configparser.ConfigParser()
cf.read('ConfigSample.ini')
for s in cf.sections():
    #print(cf.options(s))
    if ('donotlist' in cf.options(s)):
        if (cf.get(s,'DoNotList') == '0'):
            print(s)
            #outputFile.write(s + '\n')
    elif ('mustdisplay' in cf.options(s)):
            print(s)
            #outputFile.write(s + '\n')
    else:
        print('CHECK= ' + s)
        #outputFile.write('CHECK= ' + s + '\n')
#outputFile.close()


