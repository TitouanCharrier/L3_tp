
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

#define NUM_NODES 20

// Fonction pour générer un nombre aléatoire dans un intervalle donné
float rand_in_range(float min, float max) {
    return min + ((float)rand() / (float)(RAND_MAX)) * (max - min);
}

int main() {
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Créer un graphe non orienté (sans arêtes)
    Agraph_t *g = agopen("G", Agundirected, NULL);

    // Tableau pour stocker les nœuds
    Agnode_t *nodes[NUM_NODES];

    // Création des nœuds avec des positions aléatoires
    for (int i = 0; i < NUM_NODES; i++) {
        char node_name[10];
        snprintf(node_name, sizeof(node_name), "Node%d", i);

        // Créer chaque nœud
        nodes[i] = agnode(g, node_name, 1);

        // Définir une position aléatoire pour chaque nœud dans l'espace 2D
        float x = rand_in_range(-10.0, 10.0);  // Coordonnée x aléatoire
        float y = rand_in_range(-10.0, 10.0);  // Coordonnée y aléatoire

        // Appliquer la position (x, y) au nœud
        char pos_value[20];
        snprintf(pos_value, sizeof(pos_value), "%f,%f!", x, y);
        agset(nodes[i], "pos", pos_value);
    }

    // Initialiser le contexte Graphviz
    GVC_t *gvc = gvContext();

    // Disposer le graphe (calculer les positions des nœuds et des arêtes, mais ici sans arêtes)
    gvLayout(gvc, g, "dot");

    // Générer l'image en format PNG et l'enregistrer dans un fichier
    gvRenderFilename(gvc, g, "png", "graph.png");

    // Libérer les ressources utilisées
    gvFreeContext(gvc);
    agclose(g);

    printf("Graph generated as 'random_positions_graph.png'\n");

    return 0;
}

