package java_studyings.websocket;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.MessageDigest;
import java.util.Base64;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class WebSocketServer {
    public static void main(String[] args) throws Exception {
        Scanner userInputSpace = new Scanner(System.in);
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server started on port 8080. Waiting for handshake...");

        try (Socket client = server.accept();
                InputStream in = client.getInputStream();
                OutputStream out = client.getOutputStream()) {

            String data = new Scanner(in, "UTF-8").useDelimiter("\\r\\n\\r\\n").next();
            Matcher get = Pattern.compile("^GET").matcher(data);

            if (get.find()) {
                System.out.print(data);
                Matcher match = Pattern.compile("Sec-WebSocket-Key: (.*)").matcher(data);
                match.find();
                String key = match.group(1).trim();

                byte[] response = (key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11").getBytes("UTF-8");
                String accept = Base64.getEncoder().encodeToString(MessageDigest.getInstance("SHA-1").digest(response));

                byte[] handshake = ("HTTP/1.1 101 Switching Protocols\r\n" +
                        "Upgrade: websocket\r\n" +
                        "Connection: Upgrade\r\n" +
                        "Sec-WebSocket-Accept: " + accept + "\r\n\r\n").getBytes("UTF-8");

                out.write(handshake, 0, handshake.length);
                System.out.println("Handshake complete!");

                while (true) {
                    byte[] header = new byte[2];
                    in.read(header);

                    if ((header[0] & 0xFF) == 0x81) {
                        long length = header[1] & 0x7F;

                        if (length == 126) {
                            byte[] extended = new byte[2];
                            in.read(extended);
                            length = ((extended[0] & 0xFF) << 8) | (extended[1] & 0xFF);
                        }

                        byte[] mask = new byte[4];
                        in.read(mask);

                        byte[] payload = new byte[(int) length];
                        in.read(payload);

                        byte[] decoded = new byte[(int) length];
                        for (int i = 0; i < length; i++) {
                            decoded[i] = (byte) (payload[i] ^ mask[i % 4]);
                        }

                        String message = new String(decoded, "UTF-8");
                        System.out.println("Received: " + message);

                        if (message.equalsIgnoreCase("exit"))
                            break;

                        System.out.println("\n Resposta: \n");
                        byte[] myAnswer = userInputSpace.nextLine().getBytes("UTF-8");
                        out.write(0x81);
                        out.write(myAnswer.length); 
                        out.write(myAnswer);
                        out.flush();
                    }
                }
            }
        }
    }
}
