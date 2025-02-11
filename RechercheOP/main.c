#include "main.h"

int main(void) {

    tsp_t p = create_random_instance(100);
    int* parcours = malloc(p.nbr * sizeof(int));
    init_parcours(parcours, p.nbr);

    //fill_parcours_random(parcours, p.nbr);
    greedy0(p, parcours);
    //brut_force(&p, parcours);
    //test(p,parcours);
    
    write_graphviz(fopen("graph.dot", "w"),p,parcours);
    printf("Longueur : %f\n", longueur(p, parcours));
}
