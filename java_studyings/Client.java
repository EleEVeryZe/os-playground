package javaStudyings;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] argv) {
        String hostname = "localhost";
        int PORT = 8083;

        System.out.println("Starting the Client...");
        String input = "";
        Scanner scanner = new Scanner(System.in);
        System.out.print("Hi, how are you?\n");
        while ((input = scanner.nextLine()) != "-e") {
            try (Socket socket = new Socket(hostname, PORT)) {
                PrintWriter pw = new PrintWriter(socket.getOutputStream(), true);
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                pw.write(input + "\n");
                pw.flush();
                String response = br.readLine();
                System.out.print(response);
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        scanner.close();
    }
}