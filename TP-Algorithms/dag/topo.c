/**
 * @file topo.c
 *
 * @brief This file implements based on the topological ordering.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../graph/graph.h"
#include "../stack/stack.h"


/**
 * @brief Function to perform a topological sort of a graph. Update the field topological_ordering of the graph.
 *
 * @param graph The graph to be sorted.
 */
void topologicalSort(Graph graph) {
    int n = graph.numberVertices;

    /* visited[i] = 1 si le sommet i a déjà été visité */
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    /* pile DFS : les sommets en cours d'exploration */
    Stack dfsStack = NULL;

    /* pile résultat : on empile u APRÈS avoir traité tous ses successeurs
       → quand on la dépile de haut en bas, on obtient l'ordre topologique */
    Stack pile = NULL;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        push(&dfsStack, i);
        visited[i] = 1;

        while (!isStackEmpty(dfsStack)) {
            int u = peek(dfsStack);

            /* chercher un voisin non visité */
            List voisins = graph.array[u];
            int trouve = 0;
            while (voisins != NULL) {
                if (!visited[voisins->value]) {
                    visited[voisins->value] = 1;
                    push(&dfsStack, voisins->value);
                    trouve = 1;
                    break;
                }
                voisins = voisins->nextCell;
            }

            if (!trouve) {
                /* tous les successeurs de u traités → on le met dans la pile résultat */
                pop(&dfsStack);
                push(&pile, u);
            }
        }
    }

    /* dépiler pile dans topological_ordering
       premier dépilé = source (index 0), dernier = puits (index n-1) */
    for (int i = 0; i < n; i++)
        graph.topological_ordering[i] = pop(&pile);
}




/* ===== VERSION ENTRAINEMENT ===== */
void topologicalSort_training(Graph graph) {
    Stack *stack = createStack();
    Stack *final = createStack();
    int n = graph.numberVertices;
    int visited[n];
    for(int i =0 ; i < n ; i ++){
        visited[i] = 0;
    }
    for(i = 0; i < n ; i ++){
        if(visited[i]) continue;
        push(stack, i);
        visited[i] = 1;
        while(isStackEmpty(stack) == 0){
            int u = peek(stack);
            List voisin = g.array[u];
            int trouve = 0;
            while(voisin != NULL){
                if(visited[voisin->value] == 0){
                    visited[voisin->value] = 1;
                    push(stack, voisin->value);
                    trouve = 1 ;
                    break;
                }
                voisin = voisin->nextCell;
            }
            if(trouve == 0){
                pop(stack);
                push(pile, u);
            }
        }
    }
    for(i =0; i<n; i++){
        graph.topological_ordering[i] = pop(pile);
    }
}


/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */
void computeEarliestStartDates(Graph graph) {
    /* on a besoin de l'ordre topologique pour la passe avant */
    topologicalSort(graph);
    int n = graph.numberVertices;

    /* initialiser toutes les dates au plus tôt à 0
       (les sources n'ont pas de prédécesseurs, elles commencent à 0) */
    for (int i = 0; i < n; i++)
        graph.earliest_start[i] = 0.0;

    /* passe avant : on parcourt dans l'ordre topologique
       quand on traite u, TOUS ses prédécesseurs ont déjà été traités
       → on propage la date vers les successeurs v */
    for (int i = 0; i < n; i++) {
        int u = graph.topological_ordering[i];
        List voisins = graph.array[u];
        while (voisins != NULL) {
            int v = voisins->value;
            /* poids de l'arête = distance euclidienne entre u et v */
            double w = distance(graph.xCoordinates[u], graph.yCoordinates[u],
                                graph.xCoordinates[v], graph.yCoordinates[v]);
            /* v ne peut démarrer qu'après que u soit terminé :
               si ce chemin est plus long que ce qu'on avait, on met à jour */
            if (graph.earliest_start[u] + w > graph.earliest_start[v])
                graph.earliest_start[v] = graph.earliest_start[u] + w;
            voisins = voisins->nextCell;
        }
    }
}

/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */
/* ===== VERSION ENTRAINEMENT ===== */
void computeEarliestStartDates_training(Graph graph){
    topologicalSort(graph);
    int n = graph.numberVertices;

    for( int i =0; i < n; i++){
        graph.earliest_start[i] = 0.0;
    }

    for(int i = 0; i < n; i++){
        int u = graph.topological_ordering[i];
        List voisins = graph.array[u];

        while(voisins != NULL){
            int w = distance(graph.xCoordinates[voisin.value], graph.yCoordinates[voisin.value], graph.xCoordinates[u], graph.yCoordinates[u]);
            if(graph.earliest_start[u] + w > graph.earliest_start[voisin.value]){
                graph.earliest_start[voisin.value] = graph.earliest_start[u] + w
            }
            voisins = voisins.nextCell;
        }
    }
}


/**
 * @brief Function to compute the latest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the latest start dates.
 * Updates the array containing the latest start date of each vertex in the graph structure.
 */
void computeLatestStartDates(Graph graph) {
    /* on a besoin des dates au plus tôt pour calculer les dates au plus tard */
    computeEarliestStartDates(graph);
    int n = graph.numberVertices;

    /* T = durée totale du projet = maximum des dates au plus tôt */
    double T = 0.0;
    for (int i = 0; i < n; i++)
        if (graph.earliest_start[i] > T)
            T = graph.earliest_start[i];

    /* initialiser toutes les dates au plus tard à T
       (les puits n'ont pas de successeurs, ils peuvent démarrer au plus tard à T) */
    for (int i = 0; i < n; i++)
        graph.latest_start[i] = T;

    /* passe arrière : on parcourt dans l'ordre topologique INVERSÉ
       pour chaque u, on regarde ses successeurs v :
       u doit terminer avant que v puisse démarrer
       → latest_start[u] ≤ latest_start[v] - distance(u,v) */
    for (int i = n - 1; i >= 0; i--) {
        int u = graph.topological_ordering[i];
        List voisins = graph.array[u];
        while (voisins != NULL) {
            int v = voisins->value;
            double w = distance(graph.xCoordinates[u], graph.yCoordinates[u],
                                graph.xCoordinates[v], graph.yCoordinates[v]);
            /* si démarrer plus tôt est obligatoire pour ne pas retarder v */
            if (graph.latest_start[v] - w < graph.latest_start[u])
                graph.latest_start[u] = graph.latest_start[v] - w;
            voisins = voisins->nextCell;
        }
    }
}
