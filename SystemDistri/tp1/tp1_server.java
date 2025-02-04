import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class Serveur {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Serveur <port_local_ecoute>");
            return;
        }

        int port = Integer.parseInt(args[0]);

        try (DatagramSocket socket = new DatagramSocket(port)) {
            System.out.println("Serveur en écoute sur le port " + port + "...");

            while (true) {
                byte[] buffer = new byte[1024];
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

                // Réception du paquet
                socket.receive(packet);

                // Conversion des données reçues en chaîne
                String message = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Message reçu : " + message);

                // Réponse au client
                String response = "Message reçu : " + message;
                byte[] responseData = response.getBytes();
                DatagramPacket responsePacket = new DatagramPacket(
                        responseData, responseData.length,
                        packet.getAddress(), packet.getPort()
                );
                socket.send(responsePacket);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
