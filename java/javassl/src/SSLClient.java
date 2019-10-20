import java.io.*;
import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;

class SSLClient {

    private SSLSocket socket = null;

    public SSLClient(String ip, int port) throws IOException {
        SSLSocketFactory socketFactory = (SSLSocketFactory)
                SSLSocketFactory.getDefault();
        socket = (SSLSocket) socketFactory.createSocket(ip, port);
    }

    public void connect() {
        try {

            PrintWriter output = new PrintWriter(
                    new OutputStreamWriter(socket.getOutputStream()));
//            byte[] c_send = {};
//            System.in.read(c_send);

            output.println("hello server");
            output.flush();


            BufferedReader input = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));

            String c_recv = input.readLine();
            c_recv += "\n " + input.readLine();
            System.out.println(c_recv);

            output.close();
            input.close();
            socket.close();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        } finally {
            System.exit(0);
        }
    }

    public static void main(String args[]) throws IOException {
        new SSLClient("127.0.0.1",9090).connect();
    }
}