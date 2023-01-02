#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

/*
 * Fügt einen Knoten mit der Telefonnummer phone und dem Namen name
 * in den Binären Suchbaum bst ein.  Für den Suchbaum soll die
 * Eigenschaft gelten, dass alle linken Kinder einen Wert kleiner
 * gleich (<=) und alle rechten Kinder einen Wert größer (>) haben.
 */
void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
    if (find_node(bst, phone) != NULL) {
        return;
    }
    bst_node *newNode = calloc(1, sizeof(bst_node));
    newNode->phone = phone;
    printf("%s\n", name);
    newNode->name = calloc(1, sizeof(strlen));
    strcpy(newNode->name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    bst->count = bst->count + 1;
    if (bst->count == 1) {
        bst->root = newNode;
        newNode->parent = NULL;
        return;
    }
    bst_node *refNode = calloc(1, sizeof(bst_node));
    refNode = bst->root;
    while (1) {
        if (phone < refNode->phone) {
            if (refNode->left == NULL) {
                refNode->left = newNode;
                newNode->parent = refNode;
                break;
            }
            refNode = refNode->left;
        } else if (phone > refNode->phone) {
            if (refNode->right == NULL) {
                refNode->right = newNode;
                newNode->parent = refNode;
                break;
            }
            refNode = refNode->right;
        }
    }
    // free(refNode);
}

/*
 * Diese Funktion liefert einen Zeiger auf einen Knoten im Baum mit
 * dem Wert phone zurück, falls dieser existiert.  Ansonsten wird
 * NULL zurückgegeben.
 */
bst_node* find_node(bstree* bst, unsigned long phone) {
    // bst_node *refNode = malloc(sizeof(bst_node));
    bst_node *refNode = calloc(1, sizeof(bst_node));
    refNode = bst->root;
    while(refNode != NULL) {
        if (phone < refNode->phone) {
            refNode = refNode->left;
        } else if (phone > refNode->phone) {
            refNode = refNode->right;
        } else if (phone == refNode->phone) {
            return refNode;
        }
    }
    return NULL;
}

/* Gibt den Unterbaum von node in "in-order" Reihenfolge aus */
void bst_in_order_walk_node(bst_node* node) {
    if (node != NULL) {
        bst_in_order_walk_node(node->left);
        print_node(node);
        bst_in_order_walk_node(node->right);
    }
}

/* 
 * Gibt den gesamten Baum bst in "in-order" Reihenfolge aus.  Die
 * Ausgabe dieser Funktion muss aufsteigend soriert sein.
 */
void bst_in_order_walk(bstree* bst) {
    if (bst != NULL) {
        bst_in_order_walk_node(bst->root);
    }
}

/*
 * Löscht den Teilbaum unterhalb des Knotens node rekursiv durch
 * "post-order" Traversierung, d.h. zurerst wird der linke und dann
 * der rechte Teilbaum gelöscht.  Anschließend wird der übergebene
 * Knoten gelöscht.
 */
void bst_free_subtree(bst_node* node) {
    if (node->left != NULL) {
        bst_free_subtree(node->left);
    }
    if (node->right != NULL) {
        bst_free_subtree(node->right);
    }
    free(node->name);
    free(node);
}

/* 
 * Löscht den gesamten Baum bst und gibt den entsprechenden
 * Speicher frei.
 */
void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}
