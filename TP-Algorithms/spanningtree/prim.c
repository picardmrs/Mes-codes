/**
 * @file prim.c
 *
 * @brief This file implements a graph data structure using a table of lists.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../graph/graph.h"
#include "../heap/heap.h"

/**
 * @brief Function that computes a minimum spanning tree of graph g of the connex component of the vertex s
 *
 * @param graph The graph
 * @param s Index of the initial vertex of the Prim procedure.
 *
 * The array parents is updated so that it contains the spanning tree
 * computed by the Prim algorithm.
 * Note that the array parents must be initialized before calling the function.
 */
void Prim(Graph g, int s) {
    int n = g.numberVertices;

    Heap *heap = createHeap(n);

    /* lignes 1-3 : insérer TOUS les sommets dans F avec clé[u] = +infini */
    for (int i = 0; i < n; i++) {
        g.parents[i] = -1;          /* préd[u] = RIEN */
        insertHeap(heap, i, INFINITY);   /* clé[u] = +infini */
    }

    /* ligne 4 : clé[depart] = 0 → il sera extrait en premier */
    modifyPriorityHeap(heap, s, 0.0);

    /* ligne 6 : tant que F ≠ ∅ */
    while (heap->nbElements > 0) {

        /* ligne 7 : extraire le sommet de clé minimale */
        int u = removeElement(heap);

        /* lignes 8-11 : pour chaque voisin v de u */
        List voisins = g.array[u];
        while (voisins != NULL) {
            int v = voisins->value;
            double w = distance(g.xCoordinates[u], g.yCoordinates[u],
                                g.xCoordinates[v], g.yCoordinates[v]);

            /* si v ∈ F (encore dans le tas) et w(u,v) < clé[v] */
            if (heap->position[v] != -1 && w < heap->priority[v]) {
                g.parents[v] = u;             /* préd[v] ← u */
                modifyPriorityHeap(heap, v, w); /* clé[v] ← w(u,v) */
            }

            voisins = voisins->nextCell;
        }
    }

    free(heap->heap);
    free(heap->position);
    free(heap->priority);
    free(heap);
}

/* ===== VERSION ENTRAINEMENT ===== */
void Prim_training(Graph g, int s) {
   Heap h = createHeap(n);
   int n = g.numberVertices;

   for (int i = 0 ; i < n; i++){
      g.parents[i] = -1;
      insertHeap(h, i, INFINITY);
   }

   insertHeap(h,s, 0.0);

   while(h->nbElements > 0){
      int u= getElement(h);

      List voisins = g.array[u];
      while(voisins != NULL){
         int v = voisin->value;
         int w = distance(g.xCoordinates[u], g.yCoordinates[u],g.xCoordinates[v], g.yCoordinates[v]);

         if(h->position[v] != -1 && w < h->priority[v]){
            h->priority[v] = w;
            g.parents[v] = u;
         }
         voisin = voisin->nextCell;
      }
   }
   free(h->position);
   .... sur les free
}
