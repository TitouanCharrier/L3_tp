#include "../main.h"

double test(tsp_t p, int parcours[p.nbr]) {
    //déterminer la médiane des distances au point de départ O(n)
    double mediane;
    double dist_to_center[p.nbr];

    for (int i=0; i<p.nbr; ++i) {
        dist_to_center[i] = distance(p, 0, i);    
    }

    qsort(dist_to_center, p.nbr, sizeof(double), compare);
    mediane = dist_to_center[(p.nbr-1)/2];
    printf("mediane : %f\n", mediane);

    int actual = 1;
    int potential = 1;
    double score;
    double min_score = INFINITY;
    
    /*for (int i=0; i<p.nbr; +i) {
        for (int j=0; j<p.nbr ; ++j) {
            if (!visited[j]) {
                score += calculer_angle(p, actual, j);
                score += distance(p, 0, j);
                if (score < min_score) {
                    min_score = score;
                    potential = j;
                }
            }
        }
        //printf("parcours to nearest : %d, %d\n", actual, nearest);
        parcours[i] = potential;
        visited[nearest] = 1;
        actual = nearest;
        smallerDistance = -1;
    } */

    //déterminer le score de chaque points en fonction
    // de sa distance au cercle
    // de sa distance au point principale
    
}
