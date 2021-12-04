from urllib import request
import re
import datetime
import os


def http_get(url):
    response = request.urlopen(url)
    page = response.read()
    return page.decode('utf-8')


url = 'http://ftp.mozilla.org/pub/firefox/releases/51.0.1/win32/en-US/'
tmp1 = http_get(url)
print(tmp1)


def ver_get(page):
    reg = re.compile(r'<tr>\s+<td>\w+</td>\s+<td><a href=.*>(.*)</a></td>\s+<td>\w+</td>\s+<td>(.*)</td>\s+</tr>')
    return reg.findall(page)


def newest_get(ver_list):
    newest = datetime.datetime(1970, 1, 1)
    index = 0
    current = 0
    for item in ver_list:
        nexttime = datetime.datetime.strptime(item[1], '%d-%b-%Y %H:%M')
        if nexttime > newest:
            newest = nexttime
            index = current
        current += 1
    return index


ver_list = ver_get(tmp1)
print(ver_list)
print(newest_get(ver_list))


def download(url, filename):
    request.urlretrieve(url, filename)

def install(filename):
    cmd = os.popen("adb install " + filename)
    print(cmd.read())

print(netstat.read())
