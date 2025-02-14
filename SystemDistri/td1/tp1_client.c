#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

enum requete_t {
    FIN=0,
    FACTORIEL,
    PUISSANCE,
    STATS
};

typedef struct requete {
    enum requete_t requeteType;
    long size;
} requete;

#define TAILLEBUF 20

int main(int argc, char *argv[]) {
    if (argc == 2) {
        printf("L'argument passé est : %s\n", argv[1]);
    } else {
        printf("Veuillez fournir un argument.\n");
    }

// identifiant de la machine serveur
struct hostent *serveur_host;
// adresse de la socket coté serveur
static struct sockaddr_in addr_serveur;
// taille de l'addresse socket
socklen_t lg;
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


// récupération identifiant du serveur
serveur_host = gethostbyname(argv[1]);
if (serveur_host==NULL) {
perror("erreur adresse serveur");
exit(1);
}

// création d'une socket UDP
sock = socket(AF_INET, SOCK_DGRAM, 0); //SOCK_STREAM pour du TCP
if (sock == -1) {
perror("erreur création socket");
exit(1);
}

// création adresse socket destinatrice
bzero(&addr_serveur, sizeof(struct sockaddr_in));
addr_serveur.sin_family = AF_INET;
addr_serveur.sin_port = htons(4000);
memcpy(&addr_serveur.sin_addr.s_addr,
serveur_host -> h_addr, serveur_host -> h_length);

// TP1 --------------------------------------------------------------------------------------------

/* on envoie le message "bonjour" au serveur
lg = sizeof(struct sockaddr_in);
nb_octets = sendto(sock, msg, strlen(msg)+1,
0,(struct sockaddr*)&addr_serveur, lg);
if (nb_octets == -1) {
perror("erreur envoi message");
exit(1); }
printf("paquet envoyé, nb_octets = %d\n",nb_octets);


// on attend la réponse du serveur
nb_octets = recvfrom(sock, buffer, TAILLEBUF, 0,(struct sockaddr*)&addr_serveur, &lg);
if (nb_octets == -1) {
perror("erreur réponse serveur");
exit(1);
}
reponse = (char *)malloc(nb_octets * sizeof(char));
memcpy(reponse, buffer, nb_octets);
printf("reponse recue du serveur : %s\n",reponse);
*/

// TD1 --------------------------------------------------------------------------------------------

//appel de factoriel 
long res = factoriel(5);
if (res == -1) perror ("Factoriel");
else printf("factoriel de 5 = %ld\n", res);

int données [] = {1,2,3,4,5};
struct res_analyse_donnée analyse;
if analyser_donnée(donnes, 5, &analyse) == 1)
perror("Analyse données");
printf("min = %d max = %d, moy = %f\n", analyse.min, analyse.max,analyse.moy);

requete ma_requete = malloc(sizeof(requete));


// on ferme la socket
close(sock);
}





















