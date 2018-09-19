import socket
import ssl
import sys


def sslClient(host, port):
        ssl_context = ssl.create_default_context(cafile='RootCA.pem')
        ssl_context.load_cert_chain("Client.pem", "Client.key")

        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        with ssl_context.wrap_socket(client, server_hostname='Server') as ssl_client:
            conn = ssl_client.connect((host , port))
            while True:
                send_data = input("send:")
                ssl_client.sendall(send_data.encode())
                recv_data = ssl_client.recv(1024)
                print("recv:%s" % recv_data)


if __name__ == '__main__':
    sslClient(sys.argv[1], int(sys.argv[2]))