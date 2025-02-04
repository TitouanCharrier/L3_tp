#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

/* taille maximale d'une ligne lors de la lecture du fichier */
#define BUFSIZE 65536

/* Types pour un graphe orienté non pondéré
 * On suit ici le système proposé par Cormen */
typedef struct chainon {
    int numero_sommet;
    struct chainon* next;
    Agnode_t* node;
} chainon_t;

typedef chainon_t* liste_t;

typedef struct {
    int nbr_sommets;
    liste_t* listes;
} graphe_t;


/* Fonctions à écrire lors du TP */

// Ajoute un nouveau chaînon contenant le numéro d'un sommet du graphe
// en tête de la liste spécifiée.
// La fonction travaille en place, mais elle retourne malgré tout
// l'adresse du nouveau chaînon (la nouvelle tête de liste) ou
// bien NULL en cas d'échec (valeur utilisée pour tester que tout
// s'est bien déroulé).
chainon_t* ajouter_chainon(int numero_sommet, liste_t* liste, Agraph_t* v_graph) {

  //printf("debug deb ajouter_chainon\n"); 

  //Creation du chainon
  chainon_t* new = malloc(sizeof(chainon_t));
  if (new==NULL) return NULL;
  new->numero_sommet = numero_sommet;
  new->next = *liste;
  *liste =  new;
  
  //Ajout au graph
  char str_sommet[20];
  sprintf(str_sommet, "%d", numero_sommet, "\n");
  new->node = agnode(v_graph, str_sommet , true);
  //printf("%p\n", new->next);
  //printf("debug fin ajouter_chainon\n"); 
  return new;
}

void add_edges_to_graph(Agraph_t* v_graph, graphe_t graph, int nbr_sommets) {
 for (int i=0; i<nbr_sommets; ++i) {
    //printf("list ? : %p\n", graph.listes[i]);
    if (graph.listes[i] != NULL) {
      //printf("found a list\n");
      liste_t subject = graph.listes[i];
      while (subject->next != NULL) {
        agedge(v_graph, subject->node, subject->next->node, NULL, true);
        //printf("added edge between %d and %d\n", subject->numero_sommet, subject->next->numero_sommet);
        subject = subject->next;
      }
    }
  } 
}

// Efface intégralement le contenu d'une liste d'adjacence (en n'oubliant
// pas de libérer la mémoire allouée), puis met la valeur NULL dans le
// pointeur de la liste.
void detruire_liste(liste_t* liste) {
  //printf("debug deb detruire_liste\n"); 
  if ((*liste)->next == NULL) {
    free (*liste);
    liste = NULL;
  }
  else {
    detruire_liste(&((*liste)->next));
    free (*liste);
    liste = NULL;
  }
  printf("debug fin detruire_liste\n"); 
}

// Détruit intégralement un graphe en effaçant toutes les listes d'adjacence
// qu'il contient puis en effaçant le tableau des listes (en mettant ensuite
// la valeur NULL à la place) et en mettant le nombre de sommets à 0.
void detruire_graphe(graphe_t* graphe, int nbr_sommets) {
  for (int i=0; i<nbr_sommets; ++i) {
    detruire_liste(graphe->listes); 
  }
}

// Renvoie la longueur d'une liste chaînée.
int _longueur_liste(liste_t liste, int counter) {
	if (liste->next == NULL) return counter;
	_longueur_liste(liste->next, counter++);
}

int longueur_liste(liste_t liste) {
	_longueur_liste(liste, 0);
}

// Teste si un graphe contient une boucle.
bool contient_boucle(graphe_t graphe) {

	liste_t liste = malloc(sizeof(liste_t));
	printf("taille du graphe : %d",graphe.nbr_sommets);

	for(int i=0; i<graphe.nbr_sommets; ++i) {
		printf("on rentre dans la boucle, %d \n", i);
		liste = graphe.listes[i];
		while (liste->next != NULL) {
			printf("on rentre dans le while \n");
			if (liste->next == liste) return false;
			else liste = liste->next;
		}
	}
}











/* Parcours 
 * bool _contient_boucle(liste_t liste) {
	if (liste->next == NULL) return false;
	if (liste->next == liste) return true;
	_contient_boucle(liste->next);
}

bool __contient_boucle(liste_t* listes) {
	if (listes->next == NULL) return false;
	if (listes->next == listes) return true;
	_contient_boucle(*liste);
	__contient_boucle(listes->next);
}

bool contient_boucle(graph_t graph) {
	_contient_boucle(graph.listes);
}*/

// Calcule la densité d'un graphe orienté.
double densite(graphe_t graphe);

// Afficher l'ensemble des sommets accessibles depuis le sommet spécifié
void afficher_accessibles(graphe_t graphe, int sommet);

// Tester l'accessibilité de sommet2 depuis sommet1
bool est_accessible(graphe_t graphe, int sommet1, int sommet2);

// Écrit le code, dans le langage de Graphviz, décrivant un graphe.
void write_graphviz(FILE *f, graphe_t graphe);

// Tester la symétrie du graphe
bool est_symetrique1(graphe_t graphe);
bool est_symetrique2(graphe_t graphe);
bool est_symetrique3(graphe_t graphe);

// On renommera finalement la troisième variante ci-dessus de la façon
// suivante (pour la suite des séances).
bool est_symetrique(graphe_t graphe);



/*
 * Cette fonction charge en mémoire un graphe orienté non pondéré décrit dans
 * un fichier.
 *
 * La fonction prend deux arguments :
 *     - le nombre de sommets ;
 *     - le nom du fichier.
 *
 * Le fichier doit énumérer les voisins de chaque sommet de la façon suivante :
 *
 *     [source] cible1 cible2 cible3 etc.
 *
 * Par exemple, le fichier ressemblera à
 *
 *     [0] 1 2 3
 *     [1] 0 3
 *     [2] 1 3
 *     [3] 1 2
 * (avec ici 4 sommets)
 *
 * La fonction renvoie un tableau de taille nbr_sommets contenant des liste_t.
 *
 * Le tableau est créé à l'aide de malloc.
 *
 * */

graphe_t read_listes(unsigned int nbr_sommets, char *fname, Agraph_t* v_graph) {
    char buffer[BUFSIZE];
    const char *delimiters = " ";
    graphe_t graphe; graphe.nbr_sommets = nbr_sommets;

    graphe.listes = malloc(nbr_sommets * sizeof(liste_t));
    if (graphe.listes == NULL) { graphe.nbr_sommets = 0; return graphe; }

    /* le sommet "courant" est initialement mis à une valeur interdite */
    int c = nbr_sommets;

    FILE *myfile = fopen(fname, "r");
    if (myfile == NULL) {
        free(graphe.listes); graphe.nbr_sommets = 0; return graphe;
    }

    /* initialisation du graphe */
    for(int i = 0; i < nbr_sommets; i++) graphe.listes[i] = NULL;

    while (fgets(buffer, sizeof(buffer), myfile)) {
        char *data = strtok(buffer, delimiters);
        int d;

        while (data !=NULL) {

            if (sscanf(data, "[%d]", &d) > 0) {
                if ((d < 0) || (d >= nbr_sommets)) {
                    fprintf(stderr, "Valeur incorrecte %d\n", d);
                    detruire_graphe(&graphe, nbr_sommets); fclose(myfile); return graphe;
                }
                c = d;
            } else if (sscanf(data, "%d", &d) > 0) {
                if ((c == nbr_sommets) || (d < 0) || (d >=nbr_sommets)) {
                    fprintf(stderr, "Valeur incorrecte %d\n", d);
                    detruire_graphe(&graphe, nbr_sommets); fclose(myfile); return graphe;
                }
                // Ajout du chaînon
                if (ajouter_chainon(d, &graphe.listes[c], v_graph) == NULL) {
                    detruire_graphe(&graphe, nbr_sommets); fclose(myfile); return graphe;
                }
            } else {
                    fprintf(stderr, "Token non reconnu lors de la lecture de %d\n", d);
                    detruire_graphe(&graphe, nbr_sommets); fclose(myfile); return graphe;
            }
            data = strtok(NULL, delimiters);
        }
    }

    fclose(myfile);
    return graphe;
}



int main(void) {
   
    int nbr_sommets = 100;
    GVC_t* gvc = gvContext();
    Agraph_t* v_graph = agopen("G", Agdirected, NULL);
  
    graphe_t graph = read_listes(nbr_sommets, "data.txt", v_graph);

    add_edges_to_graph(v_graph, graph, nbr_sommets);
    

    // Définir le format de sortie
    gvLayout(gvc, v_graph, "dot");

    // Enregistrer le graphe dans un fichier
    gvRender(gvc, v_graph, "plain", stdout);
    gvRenderFilename(gvc, v_graph, "png", "graph.png");

    // Libérer les ressources
    gvFreeLayout(gvc, v_graph);
    agclose(v_graph);
    gvFreeContext(gvc);
    fprintf(stdout, "boucle : %d\n", contient_boucle(graph));
    //fprintf(stdout, "densité : %lf\n", densite(graph));
    // write_graphviz(stdout, graphe);
    //fprintf(stdout, "est_symétrique : %d\n", est_symetrique(graph));
    //fprintf(stdout, "est accessible : %d\n", est_accessible(graph, 0, 2));
    detruire_graphe(&graph, nbr_sommets);
}

