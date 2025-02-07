#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define TAILLEBUF 20

void sendBuff(char buff[182], int sock) {

    int nb_octets = send(sock, buff, 182, 0);
    if (nb_octets == -1) {
        perror("erreur envoi message");
        exit(1);
    }
    printf("message envoyé, nb_octets = %d\n", nb_octets);
}

long getFileSize(char path[100]) {
    FILE* file = fopen(path, "rb"); 
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }
    
    fseek(file, 0, SEEK_END);  // Déplacer le curseur à la fin du fichier
    long size = ftell(file);   // Récupérer la position actuelle du curseur (la taille du fichier)
    fclose(file);
    return size;
}

int sendFile(long fileSize,char path[100], int sock) {

    char buff[182];

    FILE* file = fopen(path, "rb"); 
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }
    
    int nb_segments = fileSize / 182;

    fseek(file, 0, SEEK_SET); // on place le curseur au début du fichier
    
    for(int i=0; i<=nb_segments; ++i) {
        fread(buff, 1, 182, file);
        sendBuff(buff, sock);
        memset(buff, 0, 182);

        int confirm = recv(sock, buff, 182 - 1, 0);

        if (confirm < 0) {
            perror("Erreur lors de la réception de la confirmation");
            close(sock);
            return 1;
        }
        else {
            printf("segment envoyé : %d\n", i);
        }
    }

}


int main(int argc, char *argv[]) {
    if (argc == 3) {
        printf("L'argument passé est : %s\n", argv[1]);
    } else {
        printf("Veuillez fournir deux argument.\n");
        exit(1);
    }

    // identifiant de la machine serveur
    struct hostent *serveur_host;
    // adresse de la socket coté serveur
    struct sockaddr_in addr_serveur;
    // descripteur de la socket locale
    int sock;
    // chaine à envoyer
    char *msg = "bonjour";
    // buffer de réception
    char buffer[TAILLEBUF];
    // chaine reçue en réponse
    char *reponse;
    // nombre d'octets lus ou envoyés
    int nb_octets;

    // création d'une socket TCP
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("erreur création socket");
        exit(1);
    }

    // récupération identifiant du serveur
    serveur_host = gethostbyname(argv[1]);
    if (serveur_host == NULL) {
        perror("erreur adresse serveur");
        exit(1);
    }

    // création adresse socket destinataire
    bzero(&addr_serveur, sizeof(struct sockaddr_in));
    addr_serveur.sin_family = AF_INET;
    addr_serveur.sin_port = htons(atoi(argv[2]));
    memcpy(&addr_serveur.sin_addr.s_addr,
           serveur_host->h_addr, serveur_host->h_length);

    // établir la connexion avec le serveur
    if (connect(sock, (struct sockaddr *)&addr_serveur, sizeof(struct sockaddr_in)) == -1) {
        perror("erreur de connexion au serveur");
        exit(1);
    }

    /* on envoie le message "bonjour" au serveur
    nb_octets = send(sock, msg, strlen(msg)+1, 0);
    if (nb_octets == -1) {
        perror("erreur envoi message");
        exit(1);
    }
    printf("message envoyé, nb_octets = %d\n", nb_octets);

    // on attend la réponse du serveur
    nb_octets = recv(sock, buffer, TAILLEBUF, 0);
    if (nb_octets == -1) {
        perror("erreur réponse serveur");
        exit(1);
    }*/
    char path[100] = "./msg_to_send1.txt";
    sendFile(getFileSize(path),path, sock);
    

    reponse = (char *)malloc(nb_octets * sizeof(char));
    memcpy(reponse, buffer, nb_octets);
    printf("réponse reçue du serveur : %s\n", reponse);

    // on ferme la socket
    close(sock);
}

