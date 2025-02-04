import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class Client {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java Client <nom_serveur> <port_serveur>");
            return;
        }

        String serverName = args[0];
        int serverPort = Integer.parseInt(args[1]);

        try (DatagramSocket socket = new DatagramSocket()) {
            // Préparation du message
            String message = "youpi";
            byte[] data = message.getBytes();
            InetAddress serverAddress = InetAddress.getByName(serverName);

            // Création et envoi du paquet
            DatagramPacket packet = new DatagramPacket(data, data.length, serverAddress, serverPort);
            socket.send(packet);
            System.out.println("Message envoyé : " + message);

            // Réception de la réponse
            byte[] buffer = new byte[1024];
            DatagramPacket responsePacket = new DatagramPacket(buffer, buffer.length);
            socket.receive(responsePacket);

            // Affichage de la réponse
            String response = new String(responsePacket.getData(), 0, responsePacket.getLength());
            System.out.println("Réponse du serveur : " + response);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
