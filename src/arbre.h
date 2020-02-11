#include "element.h"

typedef struct Noeud {
    Element *self;
    struct Noeud *left;
    struct Noeud *right;
} Noeud;

Noeud* create_arbre();
Noeud* construct_arbre();
Noeud* create_noeud(Element *elem, Noeud *left, Noeud *right);
void insert(Noeud *arbre, Element *elem);
void affiche_arbre(Noeud *arbre);
