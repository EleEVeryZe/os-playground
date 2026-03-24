package java_studyings.websocket;

import java.io.*;
import java.net.Socket;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ClientHandler implements Runnable {
    private final Socket socket;
    private final InputStream in;
    private final OutputStream out;
    private Scanner scanner;

    public ClientHandler(Socket socket) throws IOException {
        this.socket = socket;
        this.in = socket.getInputStream();
        this.out = socket.getOutputStream();
        this.scanner = new Scanner(in, "UTF-8");
    }

    @Override
    public void run() {
        try {
            if (handShakeIt()) {
                signalNewUser("Server: Handshake Successful. Welcome!");
                
                while (!socket.isClosed()) {
                    if (!handleTalk()) {
                        break; 
                    }
                }
            }
        } catch (Exception e) {
            System.err.println("Client Error: " + e.getMessage());
        } finally {
            cleanup();
        }
    }

    public boolean handShakeIt() throws IOException, NoSuchAlgorithmException {
        scanner.useDelimiter("\\r\\n\\r\\n");
        
        if (!scanner.hasNext()) {
            return false;
        }

        String data = scanner.next();
        Matcher get = Pattern.compile("^GET").matcher(data);

        if (get.find()) {
            Matcher match = Pattern.compile("Sec-WebSocket-Key: (.*)").matcher(data);
            if (match.find()) {
                String key = match.group(1).trim();

                byte[] response = (key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11").getBytes("UTF-8");
                String accept = Base64.getEncoder().encodeToString(
                    MessageDigest.getInstance("SHA-1").digest(response)
                );

                byte[] handshake = ("HTTP/1.1 101 Switching Protocols\r\n" +
                        "Upgrade: websocket\r\n" +
                        "Connection: Upgrade\r\n" +
                        "Sec-WebSocket-Accept: " + accept + "\r\n\r\n").getBytes("UTF-8");

                out.write(handshake, 0, handshake.length);
                out.flush();
                System.out.println("Handshake complete for " + socket.getRemoteSocketAddress());
                return true;
            }
        }
        return false;
    }

    public void signalNewUser(String answer) throws IOException {
        byte[] myAnswer = answer.getBytes("UTF-8");
        out.write(0x81); 
        out.write(myAnswer.length);
        out.write(myAnswer);
        out.flush();
    }

    private boolean handleTalk() throws IOException {
        byte[] header = new byte[2];
        int read = in.read(header);
        
        if (read == -1) return false;

        int opcode = header[0] & 0xFF;
        
        if (opcode == 0x88) return false;

        if (opcode == 0x81) {
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

            if (message.equalsIgnoreCase("exit")) {
                return false;
            }

            signalNewUser("Echo: " + message);
        }
        return true;
    }

    private void cleanup() {
        try {
            System.out.println("Cleaning up connection...");
            if (scanner != null) scanner.close();
            if (socket != null && !socket.isClosed()) socket.close();
        } catch (IOException e) {
            System.err.println("Cleanup error: " + e.getMessage());
        }
    }
}