#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

Noeud* create_arbre(Element *elem, Noeud *gauche, Noeud *droit) {
    Noeud *racine = (Noeud*) malloc(sizeof(Noeud));

    elem->value;
    elem->nb_Occurence = 0;
    elem->binary_code = 0;
    elem->next = NULL;

    racine->self = elem;
    racine->left = NULL;
    racine->right = NULL;

    return racine;
}
