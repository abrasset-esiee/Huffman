#include "caractere.h"
#include "liste.h"

typedef struct Noeud {
    Caractere *courant;
    struct Noeud *gauche;
    struct Noeud *droite;
} Noeud;

Noeud* create_noeud(Caractere *c, Noeud *g, Noeud *d);
void build_arbre(Liste *l);
// void insert(Noeud *arbre, Element *elem);
void affiche_arbre(Noeud *arbre);
