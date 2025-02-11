#ifndef MAIN_H 
#define MAIN_H

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


double distance(tsp_t p, int v1, int v2);

double longueur(tsp_t p, int parcours[p.nbr]);

void echanger(int *a, int *b);

void genererPermutations(tsp_t *p, int *parcours, int debut, int *meilleurparcours, double *meilleureDistance);

void brut_force(tsp_t *p, int *meilleurparcours);

int compare(const void *a, const void *b);

void write_graphviz(FILE *file, tsp_t p, int parcours[p.nbr]);

double greedy0(tsp_t p, int parcours[p.nbr]);

double greedy1(tsp_t p, int parcours[p.nbr], int nsteps);

double greedy2(tsp_t p, int parcours[p.nbr], int nsteps);

double recuit1(tsp_t p, int parcours[p.nbr],double temp, double seuil, double loi);

double recuit2(tsp_t p, int parcours[p.nbr],double temp, double seuil, double loi);

double test(tsp_t p, int parcours[p.nbr]);

void init_parcours(int* parcours, int nbr);

void fill_parcours_random(int* parcours, int nbr);

tsp_t create_random_instance(int nbr);

double calculer_angle(tsp_t p,int a,int b);
#endif // !MAIN_H 
