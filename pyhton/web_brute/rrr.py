from urllib import request, parse, error
import http.cookiejar

url = 'http://192.168.10.1/cgi-bin/luci'
headers = {
            'Referer': 'http://192.168.10.1/cgi-bin/luci',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:61.0) Gecko/20100101 Firefox/61.0',
            'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            'Upgrade-Insecure-Requests':'1',
            'Connection': 'Keep-Alive'
        }
post_tag = {}
post_tag['luci_username'] = 'root'
post_tag['luci_password'] = 'root'
data = parse.urlencode(post_tag).encode('utf-8')

cookie_filename = 'cookie.txt'
cookie = http.cookiejar.LWPCookieJar(cookie_filename)
handler = request.HTTPCookieProcessor(cookie)
opener = request.build_opener(handler)

req = request.Request(url, headers=headers, data=data)


try:
    resp = opener.open(req)
    print(resp.read().decode('utf-8'))
except error.HTTPError as e:
    print(e.code)

'''
resp = opener.open(req)
print(resp.read().decode('utf-8'))

cookie.save(ignore_discard=True,ignore_expires=True)
'''


