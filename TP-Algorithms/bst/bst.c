/**
 * \file bst.c
 * \brief Implementation of classical functions for BST
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Source code of the functions declared in bst.h.
 * Thes functions are to manipulate binary search trees.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bst.h"


/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
BinarySearchTree createEmptyBST() {
    BinarySearchTree tree = NULL;
    return tree;
}

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeBST(BinarySearchTree tree) {
    if(tree!= NULL){
        freeBST(tree->rightBST);
        freeBST(tree->leftBST);
        free(tree); 
    }
    return;
}


/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree addToBST(BinarySearchTree tree, int value) {
    if(tree == NULL){
        NodeBST *newnode = malloc(sizeof(NodeBST)); 
        newnode->value = value; 
        newnode->rightBST = NULL; 
        newnode->leftBST = NULL; 
        return newnode;
    }

    else {
        if(value > tree->value){
            tree->rightBST = addToBST(tree->rightBST, value);
        }
        else{
            tree->leftBST = addToBST(tree->leftBST, value);
        }
    }
    return tree;
}


/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightBST(BinarySearchTree tree) {
    int left;
    int right; 
    if(tree != NULL){
        left = heightBST(tree->leftBST);
        right = heightBST(tree->rightBST);
        return 1+ (right > left ? right : left);
    }
    else{
        return -1;
    }
}


/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
BinarySearchTree searchBST(BinarySearchTree tree, int value) {
    if(tree == NULL){
        return NULL;
    }

    if(tree->value == value){
        return tree;
    }

    else{
        if(value > tree->value){
            return searchBST(tree->rightBST, value);
        }
        else{
            return searchBST(tree->leftBST, value);
        }
    }

    return NULL;
}


/**
 * @brief Delete the root of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteRootBST(BinarySearchTree tree) {
    return NULL;
}


/**
 * @brief Delete a value from a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to delete.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteFromBST(BinarySearchTree tree, int value) {
    return NULL;
}

/**
 * @brief Build a binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A binary such tree built by successively inserting the elements of permutation.
 */
BinarySearchTree buildBSTFromPermutation(int *permutation,size_t n) {
    int i;
    BinarySearchTree tree; 
    tree = createEmptyBST();
    for(i=0; i < n ; i++){
        tree = addToBST(tree, permutation[i]); 
    }
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintBST(BinarySearchTree tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintBST(tree->rightBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", tree->value);

    prettyPrintBST(tree->leftBST, space);
}

/**

Quelles conclusions pouvez-vous tirer des résultats d’expériences que vous obtenez ?

... Répondre ici.


*/
