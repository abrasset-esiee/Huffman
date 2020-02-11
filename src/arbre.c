#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

Noeud* create_noeud(Caractere *c, Noeud *g, Noeud *d) {
    Noeud *noeud = (Noeud*) malloc(sizeof(Noeud));
    noeud->caractere = c;
    noeud->gauche = g;
    noeud->droite = d;
    return noeud;
}

// void build_arbre(Liste *l) {

// }


// void insert(Noeud *arbre, Element *elem) {
//     if (arbre != NULL) {
//         if (arbre->left == NULL) {
//             arbre->left = create_noeud(elem, NULL, NULL);
//         } else {
//             insert(arbre->left, elem);
//         }
//         if (arbre->right == NULL) {
//             arbre->right = create_noeud(elem, NULL, NULL);
//         } else {
//             insert(arbre->right, elem);
//         }
//     }
// }

void affiche_arbre(Noeud *arbre) {
    if (arbre != NULL) {
        affiche_arbre(arbre->gauche);
        printf("%c\n", arbre->caractere->valeur);
        affiche_arbre(arbre->droite);
    }
}

// nb feuilles

//

int main(int argc, char const *argv[]) {
    Noeud *arbre;
    // Element *elem1, *elem2;
    
    // elem1 = (Element*) malloc(sizeof(Element));
    // elem2 = (Element*) malloc(sizeof(Element));

    // elem1->value = 'c';
    // elem2->value = 'h';

    // arbre = create_arbre();
    // insert(arbre, elem1);
    // insert(arbre, elem2);
    // affiche_arbre(arbre);


    return 0;
}
