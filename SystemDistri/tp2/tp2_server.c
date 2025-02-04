#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>


#define TAILLEBUF 182

void writeFile(char path[100], char buff[182]) {
    FILE *file;

    // Ouvrir le fichier en mode ajout (création si nécessaire)
    file = fopen("msg_received.txt", "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Écrire le contenu du buffer à la fin du fichier
    if (fwrite(buff, 1, strlen(buff), file) < strlen(buff)) {
        perror("Erreur lors de l'écriture dans le fichier");
        fclose(file);
        return;
    }

    printf("Les données ont été ajoutées avec succès au fichier 'msg_received.txt'.\n");

    // Fermer le fichier
    fclose(file);
}

int creerSocketTCP(int port) {
    int sock;
    struct sockaddr_in addr_local;

    // Création du socket TCP
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Erreur lors de la création du socket");
        return -1;
    }

    // Liaison de la socket sur le port local
    bzero(&addr_local, sizeof(struct sockaddr_in));
    addr_local.sin_family = AF_INET;
    addr_local.sin_port = htons(port);
    addr_local.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr *)&addr_local, sizeof(addr_local)) == -1) {
        perror("Erreur bind");
        close(sock);
        return -1;
    }

    // Mise en écoute sur la socket
    if (listen(sock, 5) == -1) {
        perror("Erreur listen");
        close(sock);
        return -1;
    }

    printf("Socket TCP créé et lié au port %d, en attente de connexions...\n", port);
    return sock;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Veuillez fournir un argument (port).\n");
        return -1;
    }

    int port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        printf("Port invalide\n");
        return -1;
    }

    char path[100] = "./msg_received.txt";

    struct sockaddr_in addr_client;  // Déclaration pour la gestion du client
    socklen_t lg = sizeof(struct sockaddr_in);
    char *reponse = "Bien reçu";
    char buffer[TAILLEBUF];
    char chaine[TAILLEBUF];
    int nb_octets;

    // Création du socket TCP
    int sock = creerSocketTCP(port);
    if (sock == -1) {
        return -1;
    }

    // Attente d'une connexion d'un client
    int client_sock = accept(sock, (struct sockaddr *)&addr_client, &lg);
    if (client_sock == -1) {
        perror("Erreur accept");
        close(sock);
        return -1;
    }

    // Récupération du nom de la machine émettrice des données
    struct hostent *host_client = gethostbyaddr(&(addr_client.sin_addr), sizeof(addr_client.sin_addr), AF_INET);
    if (host_client == NULL) {
        perror("Erreur gethostbyaddr");
        close(client_sock);
        close(sock);
        return -1;
    }
    while (1) {

        // Réception des données envoyées par le client
        nb_octets = recv(client_sock, buffer, TAILLEBUF, 0);
        if (nb_octets == -1) {
            perror("Erreur réception message");
            return -1;
        }

        // Affichage du message reçu et des coordonnées de l'émetteur
        memcpy(chaine, buffer, nb_octets);

        writeFile(path, buffer);
        printf("Reçu message : %s de la part de %s sur le port %d\n", chaine, host_client->h_name, ntohs(addr_client.sin_port));

        // Envoi de la réponse au client
        nb_octets = send(client_sock, reponse, strlen(reponse) + 1, 0);
        if (nb_octets == -1) {
            perror("Erreur envoi réponse");
            return -1;
        }
    }

    // Fermeture de la socket client et du serveur
    close(client_sock);
    close(sock);

    return 0;
}

