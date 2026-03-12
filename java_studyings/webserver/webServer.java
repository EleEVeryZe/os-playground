package java_studyings.webserver;

import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.rmi.UnknownHostException;

public class webServer {
    public static void main(String[] argv) {
        System.out.println(argv[0]);
        int port = Integer.parseInt(argv[0]);

        try (ServerSocket socket = new ServerSocket(port, 8)) {
            while (true) {
                Socket client = socket.accept();

                OutputStream out = client.getOutputStream();
                String body = "<h1>Im here to learn</h1>";
                String response = "HTTP/1.1 200 OK\r\n" +
                        "Content-type: text/html;" +
                        "charset=UTF-8\r\n" +
                        "Stupid-header: WithStupidValue \r\n" +
                        "Content-Length: " + body.length() + "\r\n" +
                        "Connection: close\r\n\r\n" + body;
                out.write(response.getBytes("UTF-8"));
                out.flush();

            }

        } catch (UnknownHostException ex) {
            System.out.print(ex);
        } catch (IOException ex) {
            System.out.print(ex);
        }
    }

}
