#include "../main.h"

void greedy1(tsp_t p, int parcours[p.nbr], int nsteps) {

    double initlong = longueur(p, parcours);

    int to_exchange_1;
    int to_exchange_2;
    
    int buff;

    for (int i=0; i<nsteps; ++i) {

        to_exchange_1 = rand() % p.nbr;
        to_exchange_2 = rand() % p.nbr;
        
        buff = parcours[to_exchange_1];
        parcours[to_exchange_1] = parcours[to_exchange_2];
        parcours[to_exchange_2] = buff;

        if (longueur(p, parcours) > initlong) {

        buff = parcours[to_exchange_1];
        parcours[to_exchange_1] = parcours[to_exchange_2];
        parcours[to_exchange_2] = buff;

        }

    }

}
