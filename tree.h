// TREE: Agrupacion de datos en forma de arbol de multiples hijos por nodo

// Includes

#include "array.h"

// Tipos

struct Tree;

typedef struct Tree* Tree;

// Funciones

Tree tre_new(uchar size_variable,void* var);
//creacion de un nuevo arbol con raiz el valor dado

void tre_del(Tree* tree);
//se borra el arbol y todos los descendientes

int tre_val(Tree tree,void* val);
//obtenemos el valor principal del arbol

Tree tre_fat(Tree tree);
//da el padre del arbol

Array tre_son(Tree t);
//da el array de hijos directos de t

size_t tre_siz(Tree tree);
//numero de valores que guarda el arbol

size_t tre_len(Tree t);
//longitud del t hasta la hoja mas lejana

Tree tre_rot(Tree tree);
//busca el arbol raiz del arbol (el que no tiene padre)

Array tre_lef(Tree tree);
//busca todas las hojas de un arbol (array de trees)

int tre_is_anc(Tree a,Tree b);
//dice si a es ancestro de b

int tre_is_rot(Tree t);
//dice si un arbol es raiz

int tre_is_lef(Tree t);
//dice si un arbol es hoja

int tre_ins(Tree father,Tree son);
//se inserta al arbol padre un nuevo arbol hijo

int tre_pod(Tree tree);
//desvinculamos a tree del arbol que lo contiene

Array tre_pre(Tree tree);
// recorre el arbol en preorden (devulve array de valores)

Array tre_pos(Tree tree);
// recorre el arbol en postorden (devulve array de valores)

Array tre_lev(Tree tree);
// recorre el arbol en niveles (devulve array de valores)

void tre_prt(Tree tree,void(*print_value)(void*));
//impresion del arbol con la funcion print value



