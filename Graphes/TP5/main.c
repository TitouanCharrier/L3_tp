#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

/* taille maximale d'une ligne lors de la lecture du fichier */
#define BUFSIZE 65536

/* Types pour un graphe orienté non pondéré
 * On suit ici le système proposé par Cormen */
typedef struct chainon {
    int numero_sommet;
    struct chainon* next;
    bool colored;
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
chainon_t* ajouter_chainon(int numero_sommet, liste_t* liste, Agraph_t* v_graph, int nbr_sommets) {

  //printf("debug deb ajouter_chainon\n"); 

  //Creation du chainon
  chainon_t* new = malloc(sizeof(chainon_t));
  if (new==NULL) return NULL;
  new->numero_sommet = numero_sommet;
  new->next = *liste;
  *liste =  new;
  
  //Ajout au graph
  char str_sommet[20];
  char fixedpos[20];
  sprintf(str_sommet, "%d", numero_sommet, "\n");
  new->node = agnode(v_graph, str_sommet , true);
  //agsafeset(new->node, "pin", "true", "");
  //agsafeset(new->node, "shape", "point", "");
  agsafeset(new->node, "style", "filled", "");
  agsafeset(new->node, "width", ".4", "");      
  agsafeset(new->node, "height", ".4", "");      
  //agsafeset(new->node, "fixedsize", "true", ""); 
  agsafeset(new->node, "color", "8", ""); 

  printf("%p\n", new->next);
  printf("debug fin ajouter_chainon\n"); 
  return new;
}

void add_edges_to_graph(Agraph_t* v_graph, graphe_t graph, int nbr_sommets) {
 for (int i=0; i<nbr_sommets; ++i) {
    //printf("list ? : %p\n", graph.listes[i]);
    if (graph.listes[i] != NULL) {
      //printf("found a list\n");
      liste_t voisin = graph.listes[i];
        printf("On rentre dans le While\n");
      int j=0;
      while (voisin->next != NULL && j<10) {
        if (graph.listes[i]->node != voisin->next->node) {
          Agedge_t *arete = agedge(v_graph, graph.listes[i]->node, voisin->next->node, "test", true);
          //agset(arete, "color", agget(voisin->node, "color"));
          printf("added edge between %d and %d\n", graph.listes[i]->numero_sommet, voisin->next->numero_sommet);
          printf("noeud : %d avant next\n", i);
          voisin = voisin->next;
          printf("noeud : %d après next\n", i);
        }
        ++j;

      }
        printf("On sort du while\n");
    }
  } 
}


// Efface intégralement le contenu d'une liste d'adjacence (en n'oubliant
// pas de libérer la mémoire allouée), puis met la valeur NULL dans le
// pointeur de la liste.
void detruire_liste(liste_t* liste) {
  //printf("debug deb detruire_liste\n"); 
  if (liste == NULL) return;
  if ((*liste)->next == NULL) {
    free(*liste);
    liste = NULL;
  }
  else {
    detruire_liste(&((*liste)->next));
    free (*liste);
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

void changeListColor(liste_t liste, int color) {
  printf("entrée dans le ListeColor\n");
  char strcolor[4];
  if (liste->next == NULL){
    if ((strcmp (agget(liste->node, "color"), "z")) == 0) {
      sprintf(strcolor, "%d", rand() % 12);
      agsafeset(liste->node, "color", strcolor, "");
    }
  }

  else {
    changeListColor(liste->next, color);
    char* childcolor = agget(liste->next->node, "color");
    printf("childcolor : %s\n", childcolor);
    agsafeset(liste->node, "color", childcolor, "");
  }

}

/*
void changeColor(graphe_t graphe, int nbr_sommets, int count, int color) {
  printf("entrée dans le Color avec count = %d\n", count);
  if (count < nbr_sommets) {
    liste_t liste = graphe.listes[count];
    char* currentcolor = agget(liste->node, "color");
    if (!(currentcolor && *currentcolor)) {
      printf("Entrée dans le changeColor\n");
      changeListColor(liste, color);
    }
    changeColor(graphe, nbr_sommets, count+=1, color+=1);
    }
  }
 */
void changeColor(graphe_t graphe, int nbr_sommets, int count, int color) {
  printf("entrée dans le Color avec count = %d\n", count);
  if (count < nbr_sommets) {
    liste_t liste = graphe.listes[count];
    printf("Entrée dans le changeColor\n");
    changeListColor(liste, color);
    changeColor(graphe, nbr_sommets, count+=1, color+=1);
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
    graphe_t graphe; 
    graphe.nbr_sommets = nbr_sommets;

    graphe.listes = malloc(nbr_sommets * sizeof(liste_t));
    if (graphe.listes == NULL) { 
      graphe.nbr_sommets = 0; 
      return graphe; 
    }

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
            }
            else if (sscanf(data, "%d", &d) > 0) {
                if ((c == nbr_sommets) || (d < 0) || (d >=nbr_sommets)) {
                    fprintf(stderr, "Valeur incorrecte %d\n", d);
                    detruire_graphe(&graphe, nbr_sommets); fclose(myfile); return graphe;
                }
                // Ajout du chaînon
                if (ajouter_chainon(d, &graphe.listes[c], v_graph, nbr_sommets) == NULL) {
                    detruire_graphe(&graphe, nbr_sommets); fclose(myfile); return graphe;
                }
            }
            else {
                    fprintf(stderr, "Token non reconnu lors de la lecture de %d\n", d);
                    detruire_graphe(&graphe, nbr_sommets); fclose(myfile); return graphe;
            }
            data = strtok(NULL, delimiters);
        }
    }

    fclose(myfile);
    return graphe;
}

graphe_t create_dag(int nbr_sommets, float densite, Agraph_t* v_graph) {

    graphe_t graphe; 
    graphe.nbr_sommets = nbr_sommets;
    graphe.listes = malloc(nbr_sommets * sizeof(liste_t));
   
    for(int i = 0; i < nbr_sommets; i++) graphe.listes[i] = NULL;
    
    
    for (int i=0; i<nbr_sommets ; ++i) {
        ajouter_chainon(i, &graphe.listes[i], v_graph, nbr_sommets);
    }

    for (int i=0; i<nbr_sommets ; ++i) {
        liste_t subject = graphe.listes[i];
        for (int j=0; j < densite * 10; ++j) {
            int randomNumber = (i + rand() %4 + 1);
            printf("randomNumber : %d\n", randomNumber);
            if (randomNumber < nbr_sommets) {
                subject->next = graphe.listes[randomNumber];
                subject = subject->next;
            }
        }
    }

    printf("debug edge\n");
    add_edges_to_graph(v_graph, graphe, nbr_sommets);
    printf("edges added\n");
    return graphe;
}



int main(void) {

    srand(time(NULL));
   
    int nbr_sommets = 100;
    GVC_t* gvc = gvContext();
    Agraph_t* v_graph = agopen("G", Agdirected, NULL);
    
    //graphe_t graph = read_listes(nbr_sommets, "data.txt", v_graph);
    graphe_t graphe = create_dag(nbr_sommets, 0.5, v_graph);  

    agattr(v_graph, AGEDGE, "penwidth", "1");  
    agattr(v_graph, AGNODE, "colorscheme", "paired12");  
    agattr(v_graph, AGEDGE, "colorscheme", "paired12");  
    agattr(v_graph, AGNODE, "color", "2");  
    agsafeset(v_graph, "rankdir", "LR", "");

    //changeColor(graphe, nbr_sommets, 0, 1);

    printf("debug edge passed\n");
    // Définir le format de sortie
    gvLayout(gvc, v_graph, "dot");

    // Enregistrer le graphe dans un fichier
    gvRender(gvc, v_graph, "plain", stdout);
    gvRenderFilename(gvc, v_graph, "png", "graph.png");
    gvRenderFilename(gvc, v_graph, "dot", "graph.dot");

    // Libérer les ressources
    gvFreeLayout(gvc, v_graph);
    agclose(v_graph);
    gvFreeContext(gvc);
    //fprintf(stdout, "boucle : %d\n", contient_boucle(graph));
    //fprintf(stdout, "densité : %lf\n", densite(graph));
    // write_graphviz(stdout, graphe);
    //fprintf(stdout, "est_symétrique : %d\n", est_symetrique(graph));
    //fprintf(stdout, "est accessible : %d\n", est_accessible(graph, 0, 2));
    //detruire_graphe(&graph, nbr_sommets);
}

