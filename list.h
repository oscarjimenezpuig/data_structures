// LIST: Creacion de una lista para cualquier tipo de valores (primero que entra, primero que sale)

// Includes

#include <stdlib.h>

#include "value.h"

// Tipos

struct List;

typedef struct List* List;

// Funciones 

List lst_new(size_t size_value);
//se crea un stack

void lst_del(List* lst);
//se libera el espacio del stack

int lst_psh(List lst,void* val);
//se introduce un valor en la cola de la lista

int lst_pop(List lst,void* val);
//se obtiene el primer valor de la lista si existe

size_t lst_siz(List lst);
//da el tamaño de la lista

