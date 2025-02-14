#include "main.h"

int main(void) {

    srand(2024);

    tsp_t p = create_random_instance(12);
    int* parcours = malloc(p.nbr * sizeof(int));
    init_parcours(parcours, p.nbr);

    //fill_parcours_random(parcours, p.nbr);
    greedy0(p, parcours);
    write_graphviz(fopen("graph_greedy0.dot", "w"),p,parcours);
    printf("Longueur greedy0 : %f\n", longueur(p, parcours));
    greedy1(p, parcours, 100);
    write_graphviz(fopen("graph_greedy1.dot", "w"),p,parcours);
    printf("Longueur greedy1 : %f\n", longueur(p, parcours));
    //brut_force(&p, parcours);
    //test(p,parcours);
    
    //write_graphviz(fopen("graph_test.dot", "w"),p,parcours);
    //printf("Longueur test: %f\n", longueur(p, parcours));
}
