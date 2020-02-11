#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

Noeud* create_arbre() {
    Noeud *racine = (Noeud*) malloc(sizeof(Noeud));
    Element *elem = (Element*) malloc(sizeof(Element));

    elem->value;
    elem->nb_Occurence = 0;
    elem->binary_code = 0;
    elem->next = NULL;

    racine->self = elem;
    racine->left = NULL;
    racine->right = NULL;

    return racine;
}

Noeud* construct_arbre() {

}

Noeud* create_noeud(Element *elem, Noeud *left, Noeud *right) {
    Noeud *noeud = (Noeud*) malloc(sizeof(Noeud));

    noeud->self = elem;
    noeud->left = left;
    noeud->right = right;

    return noeud;
}

void insert(Noeud *arbre, Element *elem) {
    if (arbre != NULL) {
        if (arbre->left == NULL) {
            arbre->left = create_noeud(elem, NULL, NULL);
        } else {
            insert(arbre->left, elem);
        }

        if (arbre->right == NULL) {
            arbre->right = create_noeud(elem, NULL, NULL);
        } else {
            insert(arbre->right, elem);
        }
    }
}

void affiche_arbre(Noeud *arbre) {
    if (arbre != NULL) {
        affiche_arbre(arbre->left);
        printf("%c\n", arbre->self->value);
        affiche_arbre(arbre->right);
    }
}

// nb feuilles

//

int main(int argc, char const *argv[]) {
    Noeud *arbre;
    Element *elem1, *elem2;
    
    elem1 = (Element*) malloc(sizeof(Element));
    elem2 = (Element*) malloc(sizeof(Element));

    elem1->value = 'c';
    elem2->value = 'h';

    arbre = create_arbre();
    insert(arbre, elem1);
    insert(arbre, elem2);
    affiche_arbre(arbre);


    return 0;
}
