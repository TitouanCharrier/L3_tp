#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <assert.h>


// Type définissant une instance du problème TSP
typedef struct {
    int nbr;
    double *x;
    double *y;
} tsp_t;


// Fonctions à écrire pendant le TP
void write_graphviz(FILE *file, tsp_t p, int parcours[p.nbr]) {
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    // Écrit l'en-tête du fichier .dot
    fprintf(file, "digraph G {\n");
    fprintf(file, "layout=neato\n");
    fprintf(file, "node [ shape=point, fixedsize=true, width=.125 ]\n edge [ penwidth=2 ]");
    

    // Exemple d'ajout de noeuds et arêtes
    for (int i=0; i < p.nbr; ++i) {
        fprintf(file, "S%d [pos=\"%f,%f\"];\n", i, p.x[i],p.y[i]);
         
    }
    
    // Ferme le graphe
    fprintf(file, "}\n");

    // Ferme le fichier
    fclose(file);
    printf("Fichier DOT généré : %s\n", "graph.dot");
}
double distance(tsp_t p, int ville1, int ville2);
double longueur(tsp_t p, int parcours[p.nbr]);
double greedy0(tsp_t p, int parcours[p.nbr]);
void shuffle(tsp_t p, int parcours[p.nbr]);
double greedy1(tsp_t p, int parcours[p.nbr], int nsteps);
double greedy2(tsp_t p, int parcours[p.nbr], int nsteps);
double recuit1(tsp_t p, int parcours[p.nbr],
               double temp, double seuil, double loi);
double recuit2(tsp_t p, int parcours[p.nbr],
               double temp, double seuil, double loi);

// Écrire ici les fonctions du TP
// ==============================









/*
   Création d'une instance aléatoire du problème TSP
*/
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

int main(void) {
    int test;
    tsp_t p = create_random_instance(100);
    write_graphviz(fopen("graph.dot", "w"),p,&test);
}
