# -*- coding: utf-8 -*-
#python3.6

from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import socketserver
import threading

class myHTTPHandler(BaseHTTPRequestHandler):
    def _set_header(self):
        self.protocol = 'HTTP/1.1'
        self.send_response(200, 'OK')
        self.send_header('Content-type', 'application/json')
        self.end_headers()

    def do_GET(self):
        #获取线程名称，对比myHTTPServer和HTTPServer的线程差异
        print(threading.current_thread().getName())

        # 获取请求类型和地址（可以通过不抑制log_message来得到，一样的效果，此处只是为了留存）
        print(self.command, self.path, self.client_address)


        #显示header内容
        print(self.headers)
        #获取header指定属性的值
        print('Accept-Language', self.headers.get('Accept-Language'))

        #读取请求内容
        #如果有Content-Length，可以通过长度来读取发送的数据内容
        length = self.headers.get('Content-Length')
        if length is not None:
            rdata = self.rfile.read(int(length))
            print(rdata.decode())
            jsobBody = json.dumps(rdata.decode())

        # 发送响应
        self._set_header()
        # pyhton3必须添加encode()才能正常发送
        self.wfile.write(json.dumps({'ret1': 'hello world'}).encode())

    def do_POST(self):
        pass

    # log处理函数，通过这种方式可以抑制请求消息输出
    # def log_message(self, format, *args):
    #     pass

class myHTTPServer(socketserver.ThreadingMixIn, HTTPServer):
    allow_reuse_address = True
    pass


if __name__ == '__main__':
    server = myHTTPServer(('127.0.0.1', 9999), myHTTPHandler)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass

    server.server_close()
