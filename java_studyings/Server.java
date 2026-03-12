package java_studyings;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

public class Server {

    private static String extractFromMsg(String msg, String toBeExtracted) {
        if (msg == null || !msg.contains("|"))
            return "";

        String[] split = msg.split("\\|");

        if (split.length < 2)
            return "";

        return switch (toBeExtracted) {
            case "path" -> split[0];
            case "userName" -> split.length > 1 ? split[1] : "";
            case "friend" -> split.length > 2 ? split[2] : "";
            default -> "";
        };
    }

    public static void main(String[] argv) {
        Map<String, Socket> connections = new HashMap<>();
        try (ServerSocket server = new ServerSocket(8083, 5)) {
            System.out.print("Accepting connections\n");

            while (true) {
                Socket socket = server.accept();
                InputStream incoming = socket.getInputStream();
                BufferedReader br = new BufferedReader(new InputStreamReader(incoming));
                PrintWriter writer = new PrintWriter(socket.getOutputStream());
                while (true) {
                    String incommingMsg = br.readLine();
                    String userName = extractFromMsg(incommingMsg, "userName");
                    writer.write("Well-come aboard" + userName + "\nThe chat has " + connections.size());
                    if (connections.size() > 0) {
                        writer.write("\nYou can send direct messages to: \n");
                        for (String conKey : connections.keySet())
                            writer.write(conKey + " - ID: " + connections.get(conKey));

                    }
                    writer.write("\n");
                    writer.flush();
                }
            }
        } catch (IOException exception) {
            System.out.print("Server Exception: " + exception.getMessage());
        }

    }
}
