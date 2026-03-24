package java_studyings.websocket;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class WebSocketServer {

    private static final ExecutorService pool = Executors.newFixedThreadPool(50);

    public static void main(String[] args) {
        int port = 8080;
        
        try (ServerSocket server = new ServerSocket(port)) {
            System.out.println("Server started on port " + port + ". Waiting for connections...");

            while (true) {
                Socket client = server.accept();
                System.out.println("New connection from: " + client.getRemoteSocketAddress());

                try {
                    pool.execute(new ClientHandler(client));
                } catch (Exception e) {
                    System.err.println("Could not start thread for client: " + e.getMessage());
                    client.close(); 
                }
            }
        } catch (Exception e) {
            System.err.println("Server Error: " + e.getMessage());
        } finally {
            pool.shutdown();
        }
    }
}