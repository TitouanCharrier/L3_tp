#include "../main.h"

void init_parcours(int* parcours, int nbr) {
    for (int i=0; i<nbr; ++i) {
        parcours[i] = -1;
    }
}

void fill_parcours_random(int* parcours, int nbr) {
  for(int i=0; i < nbr; ++i) {
    parcours[i] = rand() % nbr;
    printf("parcours : %d\n", parcours[i]);
  }
}

tsp_t create_random_instance(int nbr) {
    tsp_t p;
    p.nbr = nbr;

    p.x = malloc(nbr*sizeof(double));
    assert (p.x != NULL);
    p.y = malloc(nbr*sizeof(double));
    assert (p.y != NULL);

    for (int i=0; i < nbr; i++) {
        p.x[i] = ((double) rand()) / ((double) RAND_MAX) * 4.0;
        p.y[i] = ((double) rand()) / ((double) RAND_MAX) * 4.0;

    }

    return p;
}

// Fonctions à écrire pendant le TP
void write_graphviz(FILE *file, tsp_t p, int parcours[p.nbr]) {
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    // Écrit l'en-tête du fichier .dot
    fprintf(file, "digraph G {\n");
    fprintf(file, "layout=neato\n");
    fprintf(file, "node [shape=point, fixedsize=true, width=.125 ]\n edge [ penwidth=2 ]");

    fprintf(file, "S0 [pos=\"%f,%f!\" color=red]\n", p.x[0],p.y[0]);
    

    // d'ajout de noeuds
    for (int i=1; i < p.nbr; ++i) {
        fprintf(file, "S%d [pos=\"%f,%f!\"]\n", i, p.x[i],p.y[i]);
         
    }
    
    int previous = 0;
    for (int i=0; i < p.nbr; ++i) {
        if (parcours[i] != -1) { 
            fprintf(file, "S%d -> S%d\n", previous, parcours[i] );
            previous = parcours[i];
        }
    }
    
    // Ferme le graphe
    fprintf(file, "}\n");

    // Ferme le fichier
    fclose(file);
    printf("Fichier DOT généré : %s\n", "graph.dot");
}

// Fonction de comparaison pour qsort, tri croissant
int compare(const void *a, const void *b) {
    double *x = (double *)a;
    double *y = (double *)b;

    // Retourne un nombre négatif si x < y (pour trier dans l'ordre croissant)
    if (*x < *y) return -1;
    if (*x > *y) return 1;
    return 0;  // x == y
}

double distance(tsp_t p, int v1, int v2) {
    double x1, x2, y1, y2;
    x1 = p.x[v1];
    y1 = p.y[v1];
    x2 = p.x[v2];
    y2 = p.y[v2];
    double dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return dist;
}



double longueur(tsp_t p, int parcours[p.nbr]) {
    double res = 0;
    for (int i=0; i<p.nbr; ++i) {
        res += distance(p, parcours[i], parcours[i-1]);

    }
    return res;
}

double calculer_angle(tsp_t p,int a,int c) {
    // Calcul des vecteurs
    double xa = p.x[a];
    double ya = p.y[a];
    double xb = p.x[0];
    double yb = p.y[0];
    double xc = p.x[c];
    double yc = p.y[c];

    double vx1 = xb - xa;
    double vy1 = yb - ya;
    double vx2 = xc - xa;
    double vy2 = yc - ya;


    // Calcul du produit scalaire
    double produit_scalaire = vx1 * vx2 + vy1 * vy2;

    // Calcul des normes
    double norme1 = sqrt(vx1 * vx1 + vy1 * vy1);
    double norme2 = sqrt(vx2 * vx2 + vy2 * vy2);

    // Calcul de l'angle
    double cos_angle = produit_scalaire / (norme1 * norme2);

    // Forcer la possibilité d'angles obtus
    if (cos_angle > 1) cos_angle = 1;
    if (cos_angle < -1) cos_angle = -1;

    // Calcul de l'angle en radians
    double angle = acos(cos_angle);

    // Déterminer le sens de l'angle
    double determinant = vx1 * vy2 - vx2 * vy1;
    if (determinant < 0) {
        angle = -angle;
    }

    // Forcer l'angle à être compris entre 0 et 2*PI
    if (angle < 0) {
        angle += 2 * M_PI;
    }

    return angle;
}

void shuffle(tsp_t p, int parcours[p.nbr]) {
    int j;
    int buff;
    for (int i=0; i<p.nbr; ++i) {
        j = rand() % i; 
        buff = parcours[j];
        parcours[j] = parcours[i];
        parcours[i] = buff;
    }
}


