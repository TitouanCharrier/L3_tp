#include "../main.h"

// Fonction de comparaison pour qsort
int compare2(const void *a, const void *b) {
    AngleIndice *ai1 = (AngleIndice *)a;
    AngleIndice *ai2 = (AngleIndice *)b;
    if (ai1->angle < ai2->angle) return -1;
    if (ai1->angle > ai2->angle) return 1;
    return 0;
}


double test(tsp_t p, int parcours[p.nbr]) {


    // Création de la liste d'angles et d'indices
    AngleIndice list_angle[p.nbr];

    //déterminer la médiane des distances au point de départ O(n)
    double mediane;
    list_angle[0].angle = -1;
    list_angle[0].indice = 0;
    list_angle[1].angle = -1;
    list_angle[1].indice = 1;
    int reference_point = 1;

    for (int i=2; i<p.nbr; ++i) {
        list_angle[i].angle = calculer_angle(p, reference_point, i);  
        list_angle[i].indice = i;
    }


    // Trier la liste en fonction des angles
    qsort(list_angle, sizeof(list_angle) / sizeof(list_angle[0]), sizeof(AngleIndice), compare2);
    
    for (int i=0; i<p.nbr; ++i) { 
        parcours[i] = list_angle[i].indice;
        //printf("Angle %d: %f\n", list_angle[i].indice, list_angle[i].angle);
    }
    
    //déterminer le score de chaque points en fonction
    // de sa distance au cercle
    // de sa distance au point principale
    
}
