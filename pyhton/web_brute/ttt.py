from urllib import request, parse, error
import http.cookiejar

url = 'http://192.168.10.1/cgi-bin/luci'

cookie_filename = 'cookie.txt'
cookie = http.cookiejar.LWPCookieJar(cookie_filename)
cookie.load(cookie_filename,ignore_expires=True,ignore_discard=True)
handler = request.HTTPCookieProcessor(cookie)
opener = request.build_opener(handler)

req = request.Request(url)
resp = opener.open(req)
print(resp.decode('utf-8'))
