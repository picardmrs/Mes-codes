/**
 * \file rbst.c
 * \brief Implementation of the functions related to Randomized Binary Search Trees (RBST).
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a randomized binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "rbst.h"

/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
RBinarySearchTree createEmptyRBST(){
    return NULL;
}

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeRBST(RBinarySearchTree tree){
    if(tree == NULL){
        return;
    }
    freeRBST(tree->rightRBST);
    freeRBST(tree->leftRBST);
    free(tree);
    return;
}

/**
 * @brief Compute the size of a randomized binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The number of nodes in the tree.
 */
int sizeOfRBST(RBinarySearchTree tree) {
    if(tree == NULL){
        return 0; 
    }
    return tree->size;
}

/**
 * @brief Split a randomized binary search tree into two parts according to a value.
 * @param tree The RBST to split.
 * @param value The value to split the tree on.
 * @param inf Pointer to a randomized BST that will store the final tree containing the elements strictly smaller than value.
 * @param sup Pointer to a randomized BST that will store the final tree containing the elements greater or equal to value.
 *
 * Split a randomized binary search tree into two parts according to a value.
 *
 * Be carful: the RBST tree is modified during the process but the inf and sub parts contain together
 * all the nodes of tree.
 */
void splitRBST(RBinarySearchTree tree, int value, RBinarySearchTree* inf, RBinarySearchTree* sup) {
    if(tree == NULL){
        *inf = NULL;
        *sup = NULL;
        return;
    }
    else if(tree->value >= value){
        *sup = tree;
        splitRBST(tree->leftRBST, value, inf, &tree->leftRBST);
    }
    else if(tree->value < value){
        *inf = tree;
        splitRBST(tree->rightRBST, value, &tree->rightRBST, sup);
    }
    return;
}

/**
 * @brief Insert a value at the root of a randomized binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to insert.
 * @return A pointer to the root of the modified tree.
 */
RBinarySearchTree insertAtRoot(RBinarySearchTree tree, int value) {
    RBinarySearchTree inf;
    RBinarySearchTree sup;
    NodeRBST *node = malloc(sizeof(NodeRBST));

    node->value = value;
    inf = createEmptyRBST();
    sup = createEmptyRBST(); 

    splitRBST(tree, value, &inf, &sup);
    node->leftRBST = inf;
    node->rightRBST = sup;
    node->size = 1 + sizeOfRBST(inf) + sizeOfRBST(sup);

    return node;
}


/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
RBinarySearchTree addToRBST(RBinarySearchTree tree, int value){
    if(tree == NULL){
        NodeRBST *node = malloc(sizeof(NodeRBST));
        node->value = value;
        node->size = 1;
        node->leftRBST = NULL;
        node->rightRBST = NULL;
        return node;
    }
    
    if(rand()%(tree->size + 1) == 0){
        tree = insertAtRoot(tree, value);
        return tree;
    }
    else{
        if(value < tree->value){
            tree->leftRBST = addToRBST(tree->leftRBST, value);
            tree->size++;
        }
        else{
            tree->rightRBST = addToRBST(tree->rightRBST, value);
            tree->size++;
        }
    }
    return tree;
}


/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightRBST(RBinarySearchTree tree) {
    if (tree == NULL)
        return -1;
    int leftHeight = heightRBST(tree->leftRBST);
    int rightHeight = heightRBST(tree->rightRBST);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
RBinarySearchTree searchRBST(RBinarySearchTree tree, int value){
    if (tree == NULL)
        return NULL;
    if (tree->value == value)
        return tree;
    if (value < tree->value)
        return searchRBST(tree->leftRBST, value);
    return searchRBST(tree->rightRBST, value);
}


/**
 * @brief Build a randomized binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A random binary such tree built by successively inserting the elements of permutation.
 */
RBinarySearchTree buildRBSTFromPermutation(int *permutation,size_t n) {
    RBinarySearchTree tree = createEmptyRBST();
    for (size_t i = 0; i < n; i++)
        tree = addToRBST(tree, permutation[i]);
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintRBST(RBinarySearchTree tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintRBST(tree->rightRBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("[%d,%d]\n", tree->value, tree->size);

    prettyPrintRBST(tree->leftRBST, space);
    return ;
}
