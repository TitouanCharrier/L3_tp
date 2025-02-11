#include "../main.h"

// Solution absolue --------------------------------------------------------------------
// Fonction pour échanger deux éléments dans un tableau
void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b; 
    *b = temp;
}

// Fonction récursive pour générer toutes les permutations des nœuds
void genererPermutations(tsp_t *p, int *parcours, int debut, int *meilleurparcours, double *meilleureDistance) {
    if (debut == p->nbr) {
        // Calculer la distance pour la permutation actuelle
        double distanceTotale = longueur(*p, parcours);

        // Si cette permutation est plus courte que la meilleure trouvée jusqu'à présent
        if (distanceTotale < *meilleureDistance) {
            *meilleureDistance = distanceTotale;
            // Copier le parcours actuel comme meilleur parcours
            for (int i = 0; i < p->nbr; i++) {
                meilleurparcours[i] = parcours[i];
            }
        }
        return;
    }

    // Parcours de toutes les permutations possibles
    for (int i = debut; i < p->nbr; i++) {
        echanger(&parcours[debut], &parcours[i]);
        genererPermutations(p, parcours, debut + 1, meilleurparcours, meilleureDistance);
        echanger(&parcours[debut], &parcours[i]);  // revenir à l'état précédent
    }
}


// Fonction principale pour résoudre le problème du voyageur de commerce
void brut_force(tsp_t *p, int *meilleurparcours) {
    int *parcours = (int *)malloc(p->nbr * sizeof(int));
    
    // Initialisation du tableau des nœuds
    for (int i = 0; i < p->nbr; i++) {
        parcours[i] = i;  // Chaque nœud reçoit son propre index
    }

    double meilleureDistance = INFINITY;
    
    // Générer toutes les permutations des nœuds
    genererPermutations(p, parcours, 0, meilleurparcours, &meilleureDistance);
    
    free(parcours);
}
