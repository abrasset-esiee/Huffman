#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caractere.h"



typedef struct Noeud {
    Caractere *caractere;
    struct Noeud *gauche;
    struct Noeud *droite;
} Noeud;

Noeud* create_noeud(Caractere *c, Noeud *g, Noeud *d);
void afficheArbre(Noeud *arbre, int nbTab);
void setCodes(Noeud *n);
