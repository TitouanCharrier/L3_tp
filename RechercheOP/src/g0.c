#include "../main.h"

double greedy0(tsp_t p, int parcours[p.nbr]) {

    int actual = 0;
    int visited[p.nbr];
    for (int i=0; i<p.nbr; ++i) {
        visited[i] = 0;
    }
    visited[0] = -1;
    double smallerDistance = -1;
    double score;
    int nearest;
    //printf("p.nbr %d\n", p.nbr);

    for (int i=0; i<p.nbr-1; ++i) {
        for (int j=0; j<p.nbr; ++j) {
            if (!visited[j]) {
                score = distance (p, actual, j);
                score += 0.1*(calculer_angle(p, actual, j));
                score += 0.5*(distance(p, 0, actual)) - (distance(p, 0, j));
                if (smallerDistance == -1 || smallerDistance > score) {
                    smallerDistance = score;
                    nearest = j;
                }
            }
        }
    
        //printf("parcours to nearest : %d, %d\n", actual, nearest);
        parcours[i] = nearest;
        visited[nearest] = 1;
        actual = nearest;
        smallerDistance = -1;
    }
    smallerDistance += distance (p, actual, 0);
    parcours[p.nbr-1] = 0;

    return smallerDistance;
}
