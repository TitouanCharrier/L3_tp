/*
   Commande de compilation depuis Vim :
   µ-cmd:!export myfile="%"; gcc -o "${myfile\%.c}" %; `realpath "${myfile\%.c}"`
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

// Utilisation d'une table de hachage
//   - fonction est_symetrique
//   - création d'un graphe aléatoire
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"


/* Types pour un graphe orienté non pondéré
 * On suit ici le système proposé par Cormen */
typedef struct chainon {
    int numero_sommet;
    struct chainon* next;
} chainon_t;

typedef chainon_t* liste_t;

typedef struct {
    int nbr_sommets;
    liste_t *listes;
} graphe_t;

typedef struct {
    chainon_t * debut;
    chainon_t * fin;
} file_t;


/* Fonctions à écrire lors du TP */

chainon_t *inserer_file(file_t *f, int data);
int extraire_file(file_t *f);



/* Fonctions des TP précédents */

chainon_t * ajouter_chainon(int numero_sommet, liste_t *liste) {
    chainon_t *c = malloc(sizeof(chainon_t));
    if (c==NULL) return NULL;
    c -> numero_sommet = numero_sommet;
    c -> next = *liste;
    *liste = c;
    return c;
}

void detruire_liste(liste_t *liste) {
    chainon_t *c = *liste;
    while (c != NULL) {
        chainon_t *n = c -> next;
        free(c);
        c = n;
    }
    *liste = NULL;
}

void detruire_graphe(graphe_t *graphe) {
    for (int i=0; i < graphe->nbr_sommets; i++) {
        detruire_liste(&(graphe->listes[i]));
    }
    if (graphe->listes != NULL) free(graphe->listes);
    graphe->listes = NULL;
    graphe->nbr_sommets = 0;
}


int longueur_liste(liste_t liste) {
    int n = 0;
    while (liste != NULL) {
        n++; liste = liste -> next;
    }
    return n;
}

bool contient_boucle(graphe_t graphe) {
    for(int i=0; i < graphe.nbr_sommets; i++) {
        liste_t liste = graphe.listes[i];
        while(liste != NULL) {
            if (liste->numero_sommet == i) return true;
            liste = liste -> next;
        }
    }
    return false;
}

double densite(graphe_t graphe) {
    int n = 0;
    for (int i=0; i < graphe.nbr_sommets; i++) {
        n += longueur_liste(graphe.listes[i]);
    }
    return ((double) n) / ((double) (graphe.nbr_sommets * graphe.nbr_sommets));
}

void afficher_accessibles_rec(graphe_t graphe, int sommet, int *marqueurs) {
    fprintf(stdout, "Sommet %d\n", sommet);
    liste_t liste = graphe.listes[sommet];
    while(liste != NULL) {
        int adjacent = liste->numero_sommet;
        if (marqueurs[adjacent] == 0) {
            marqueurs[adjacent] = 1;
            afficher_accessibles_rec(graphe, adjacent, marqueurs);
        }
        liste = liste -> next;
    }
}
void afficher_accessibles(graphe_t graphe, int sommet) {
    // initialisation de marqueurs (un par sommet)
    int marqueurs[graphe.nbr_sommets];
    for(int i=0; i < graphe.nbr_sommets; i++) marqueurs[i] = 0;
    marqueurs[sommet] = 1;
    afficher_accessibles_rec(graphe, sommet, marqueurs);
}

bool est_accessible_rec(graphe_t graphe, int sommet1, int sommet2, bool *marqueurs) {
    if (sommet1 == sommet2) return true;
    liste_t liste = graphe.listes[sommet1];
    while(liste != NULL) {
        int adjacent = liste->numero_sommet;
        if (!marqueurs[adjacent]) {
            marqueurs[adjacent] = true;
            if (est_accessible_rec(graphe, adjacent, sommet2, marqueurs)) return true;
        }
        liste = liste -> next;
    }
    return false;
}
bool est_accessible(graphe_t graphe, int sommet1, int sommet2) {
    // initialisation de marqueurs (un par sommet)
    bool marqueurs[graphe.nbr_sommets];
    for(int i=0; i < graphe.nbr_sommets; i++) marqueurs[i] = false;
    marqueurs[sommet1] = true;
    return est_accessible_rec(graphe, sommet1, sommet2, marqueurs);
}

void write_graphviz(FILE *f, graphe_t graphe) {
    fprintf(f, "digraph G {\n");
    for(int i=0; i < graphe.nbr_sommets; i++) {
        liste_t liste = graphe.listes[i];
        while(liste != NULL) {
            fprintf(f, "    S%d -> S%d\n", i, liste->numero_sommet);
            liste = liste -> next;
        }
    }
    fprintf(f, "}\n");
}


// On présuppose que le graphe est strict (ne contient pas de boucle)
// Pour chaque arc, il existe l'arc opposé.

bool est_symetrique(graphe_t graphe) {
    assert(!contient_boucle(graphe));
    bool result = true;

    int n = graphe.nbr_sommets;

    typedef struct { int sommet1, sommet2; } arete_t; // type pour les arêtes
    typedef struct { arete_t key; } mykey_t;  // type pour les clés de hachage

    mykey_t *hash = NULL;

    // On crée une table de hachage contenant toutes les arcs du graphe
    for(int i=0; i < n; i++) {
        liste_t liste = graphe.listes[i];
        while(liste != NULL) {
            arete_t a = (arete_t) { i, liste -> numero_sommet };
            hmputs(hash, ((mykey_t) { a }));
            liste = liste -> next;
        }
    }

    // On parcourt tous les arcs présents dans la table et on vérifie
    // l'existence (dans la même table) de l'arc opposé
    for(int i=0; i < hmlen(hash); i++) {
        arete_t a = hash[i].key;
        if ( hmgeti(hash, ((arete_t) { a.sommet2, a.sommet1 })) < 0 ) {
            // Il manque l'arc (sommet2, sommet1) opposé à (sommet1, sommet2)
            result = false;
            break;
        }
    }

    hmfree(hash);
    return result;
}




// Construction d'un graphe aléatoire

typedef struct { int sommet1, sommet2; } arete_t; // type pour les arêtes
typedef struct { arete_t key; } mykey_t;  // type pour les clés de hachage

int split_square(mykey_t **hash, int offset,
                 arete_t a1, arete_t a2, arete_t a3, arete_t a4, int rlevel) {

    // condition d'arrêt de la récursivité
    if (rlevel == 0) return 0;

    int nbr = 0;

    // les quatre arêtes forment un cycle ; on récupère le carré
    int s1 = a1.sommet1;
    int s2 = a2.sommet1;
    int s3 = a3.sommet1;
    int s4 = a4.sommet1;

    // arêtes entrante et sortante vers le point central E
    int in = rand()%4; int out = rand()%4;
    int s_in, s_out;
    switch(in) {
        case 0: s_in = s1; break;
        case 1: s_in = s2; break;
        case 2: s_in = s3; break;
        case 3: s_in = s4; break;
    }
    switch(out) {
        case 0: s_out = s1; break;
        case 1: s_out = s2; break;
        case 2: s_out = s3; break;
        case 3: s_out = s4; break;
    }

    // création du point E
    arete_t a_in  = (arete_t) { s_in, offset+nbr };
    arete_t a_out  = (arete_t) { offset+nbr, s_out };
    hmputs(*hash, ((mykey_t) { a_in }));
    hmputs(*hash, ((mykey_t) { a_out }));
    nbr++;

    // création du point F
    hmdel(*hash, a1);
    arete_t af1 = (arete_t) { s1, offset+nbr };
    arete_t af2 = (arete_t) { offset+nbr, s2 };
    if ((in != 0) || (out != 1)) {
        hmputs(*hash, ((mykey_t) { af1 }));
        hmputs(*hash, ((mykey_t) { af2 }));
        nbr++;
    }

    // création du point G
    hmdel(*hash, a2);
    arete_t ag1 = (arete_t) { s2, offset+nbr };
    arete_t ag2 = (arete_t) { offset+nbr, s3 };
    if ((in != 1) || (out != 2)) {
        hmputs(*hash, ((mykey_t) { ag1 }));
        hmputs(*hash, ((mykey_t) { ag2 }));
        nbr++;
    }

    // création du point H
    hmdel(*hash, a3);
    arete_t ah1 = (arete_t) { s3, offset+nbr };
    arete_t ah2 = (arete_t) { offset+nbr, s4 };
    if ((in != 2) || (out != 3)) {
        hmputs(*hash, ((mykey_t) { ah1 }));
        hmputs(*hash, ((mykey_t) { ah2 }));
        nbr++;
    }

    // création du point I
    hmdel(*hash, a4);
    arete_t ai1 = (arete_t) { s4, offset+nbr };
    arete_t ai2 = (arete_t) { offset+nbr, s1 };
    if ((in != 3) || (out != 0)) {
        hmputs(*hash, ((mykey_t) { ai1 }));
        hmputs(*hash, ((mykey_t) { ai2 }));
        nbr++;
    }

    // appels récursifs sur les zones vides
    if ((in != 0) && (out != 0)) {
        // Création de l'arête FE et EI
        arete_t a_fe  = (arete_t) { af1.sommet2, offset };
        arete_t a_ei  = (arete_t) { offset, ai1.sommet2 };
        hmputs(*hash, ((mykey_t) { a_fe }));
        hmputs(*hash, ((mykey_t) { a_ei }));

        nbr += split_square(hash, offset + nbr,
                     af1, a_fe, a_ei, ai2, rlevel-1);
    }
    if ((in != 1) && (out != 1)) {
        // Création de l'arête GE et EF
        arete_t a_ge  = (arete_t) { ag1.sommet2, offset };
        arete_t a_ef  = (arete_t) { offset, af1.sommet2 };
        hmputs(*hash, ((mykey_t) { a_ge }));
        hmputs(*hash, ((mykey_t) { a_ef }));

        nbr += split_square(hash, offset + nbr,
                     af2, ag1, a_ge, a_ef, rlevel-1);
    }
    if ((in != 2) && (out != 2)) {
        // Création de l'arête HE et EG
        arete_t a_he  = (arete_t) { ah1.sommet2, offset };
        arete_t a_eg  = (arete_t) { offset, ag1.sommet2 };
        hmputs(*hash, ((mykey_t) { a_he }));
        hmputs(*hash, ((mykey_t) { a_eg }));

        nbr += split_square(hash, offset + nbr,
                     a_eg, ag2, ah1, a_he, rlevel-1);
    }
    if ((in != 3) && (out != 3)) {
        // Création de l'arête IE et EH
        arete_t a_ie  = (arete_t) { ai1.sommet2, offset };
        arete_t a_eh  = (arete_t) { offset, ah1.sommet2 };
        hmputs(*hash, ((mykey_t) { a_ie }));
        hmputs(*hash, ((mykey_t) { a_eh }));

        nbr += split_square(hash, offset + nbr,
                     a_ie, a_eh, ah2, ai1, rlevel-1);
    }

    return nbr;
}

graphe_t random_graph(int rlevel) {
    graphe_t graphe;

    mykey_t *hash = NULL;

    arete_t a1 = (arete_t) { 0, 1 };
    arete_t a2 = (arete_t) { 1, 2 };
    arete_t a3 = (arete_t) { 2, 3 };
    arete_t a4 = (arete_t) { 3, 0 };
    hmputs(hash, ((mykey_t) { a1 }));
    hmputs(hash, ((mykey_t) { a2 }));
    hmputs(hash, ((mykey_t) { a3 }));
    hmputs(hash, ((mykey_t) { a4 }));

    int nbr = 4 + split_square(&hash, 4, a1, a2, a3, a4, rlevel);

    // construction du graphe
    graphe.nbr_sommets = nbr;
    graphe.listes = malloc(nbr * sizeof(liste_t));
    for(int i = 0; i < nbr; i++) graphe.listes[i] = NULL;

    for(int i=0; i < hmlen(hash); i++) {
        arete_t a = hash[i].key;
        if (ajouter_chainon(a.sommet2, &graphe.listes[a.sommet1]) == NULL) {
            detruire_graphe(&graphe); break;
        }
    }

    hmfree(hash);
    return graphe;
}



// Travail du TP3


int * distances_sommet(graphe_t graphe, int sommet);

int max_distance_sommet(graphe_t graphe, int sommet);

int diametre_graphe(graphe_t graphe);

liste_t plus_court_chemin(graphe_t graphe, int sommet1, int sommet2);


int main(void) {
    srand(time(NULL));


    graphe_t graphe = random_graph(2);
    write_graphviz(stdout, graphe);




}
