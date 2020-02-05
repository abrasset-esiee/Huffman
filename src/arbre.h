#include "element.h"

typedef struct Noeud {
    Element self;
    struct Noeud *left;
    struct Noeud *right;
} Noeud;
