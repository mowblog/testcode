import java.io.*;
import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLServerSocketFactory;
import javax.net.ssl.SSLSocket;

class SSLServer {

    private SSLServerSocket serverSocket = null;

    public SSLServer(int port) throws Exception {
        SSLServerSocketFactory socketFactory = (SSLServerSocketFactory)
                SSLServerSocketFactory.getDefault();
        serverSocket = (SSLServerSocket)socketFactory.createServerSocket(port);
    }

    private void runServer() {
        while (true) {
            try {
                System.out.println("Waiting for connection...");
                SSLSocket socket = (SSLSocket) serverSocket.accept();

                BufferedReader input = new BufferedReader(
                        new InputStreamReader(socket.getInputStream()));

                String s_recv = input.readLine();

                PrintWriter output = new PrintWriter(
                        new OutputStreamWriter(socket.getOutputStream()));

                output.println(s_recv);

                output.close();
                input.close();
                socket.close();

            } catch (IOException ioException) {
                ioException.printStackTrace();
            }
        }
    }

    public static void main(String args[]) throws Exception {
        SSLServer server = new SSLServer(9090);
        server.runServer();
    }
}