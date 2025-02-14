#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define TAILLEBUF 1024

int creerSocketUDP(int port) {
    int sock;
    struct sockaddr_in addr_local, addr_client;

    // Création du socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("Socket UDP créé et lié au port %d\n", port);
    return sock;
}

int _factoriel(int value, int tmp, int res) {
    if (value == tmp-1) return res;
    else _factoriel(value, tmp+1, res*tmp);
}

int factoriel(int value) {
    return _factoriel(value, 1, 1);
}

int handleRequest(requete req, int value) {
    switch (req.type_requete) {
        case FACTORIEL :
            return 
            
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Veuillez fournir un argument (port).\n");
        return -1;
    }

    struct sockaddr_in addr_client;  // Déclaration manquante

    int port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        printf("Port invalide\n");
        return -1;
    }

    struct hostent *host_client;
    socklen_t lg = sizeof(struct sockaddr_in);
    char *reponse = "Bien reçu";
    char buffer[TAILLEBUF];
    char chaine[TAILLEBUF];
    int nb_octets;

    // Création du socket UDP
    int sock = creerSocketUDP(port);
    if (sock == -1) {
        return -1;
    }

    // Attente de données venant d'un client
    nb_octets = recvfrom(sock, buffer, TAILLEBUF, 0, (struct sockaddr *)&addr_client, &lg);
    if (nb_octets == -1) {
        perror("Erreur réception paquet");
        close(sock);
        return -1;
    }

    // Récupération du nom de la machine émettrice des données
    host_client = gethostbyaddr(&(addr_client.sin_addr), sizeof(addr_client.sin_addr), AF_INET);
    if (host_client == NULL) {
        perror("Erreur gethostbyaddr");
        close(sock);
        return -1;
    }

    // Affichage du message reçu et des coordonnées de l'émetteur
    memcpy(chaine, buffer, nb_octets);
    printf("Reçu message : %s de la part de %s sur le port %d\n", chaine, host_client->h_name, ntohs(addr_client.sin_port));

    // Envoi de la réponse à l'émetteur
    nb_octets = sendto(sock, reponse, strlen(reponse) + 1, 0, (struct sockaddr *)&addr_client, lg);
    if (nb_octets == -1) {
        perror("Erreur envoi réponse");
        close(sock);
        return -1;
    }

    int gererClient() {

        while (1) {

            requete req;
            int value;
            ssize_t status = read(int fd, &req, sizeof(requete));

            if (status == -1) {
                perror("read");
                return 1;
            } else {
                if (req.type_requete == FACTORIEL) {
                    status = read(int fd, &value, sizeof(int));
                    return factoriel(value);
                }
            }
        }

    }
    // Fermeture de la socket
    close(sock);
    return 0;
}

