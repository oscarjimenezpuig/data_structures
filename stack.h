// STACK: Creacion de una pila para cualquier tipo de valores

// Includes

#include <stdlib.h>

#include "value.h"

// Tipos

struct Stack;

typedef struct Stack* Stack;

// Funciones 

Stack stk_new(size_t size_value);
//se crea un stack

void stk_del(Stack* stk);
//se libera el espacio del stack

int stk_psh(Stack stk,void* val);
//se introduce un valor en la cola del stack

int stk_pop(Stack stk,void* val);
//se obtiene el ultimo valor de la cola si existe

int stk_emp(Stack stk);
//dice si la pila esta o no vacia


