// ARRAY: Almacena datos uno detras de otro

// Includes

#include <stdlib.h>
#include <stdio.h>

#include "value.h"

// Tipos

struct Array;

typedef struct Array* Array;

// Funciones

Array arr_new(uchar size_variable,size_t capacity);
//definicion de array a partir del tamaño de la variable y la capacidad

void arr_del(Array* array);
//liberamos espacio del array

Array arr_cpy(Array array);
//se crea una copia con los mismos elementos que el array

size_t arr_siz(Array array);
//devuelve el tamaño del array

size_t arr_cap(Array array);
//devuelve la capacidad del array

int arr_ins(Array array,void* val);
//entramos un valor en el array

int arr_get(Array array,size_t pos,void* val);
//obtenemos el valor que ocupa la posicion pos

int arr_fnd(Array array,void* val,int (*compare)(void*,void*),size_t* pos);
//busca la posicioni de un valor val siguiendo la funcion compare (0: igual, 1 mayor el primero, -1 mayor el segundo)

int arr_era(Array a,size_t p);
//borramos el elemento que esta en la posicion p

int arr_rev(Array a);
//cambia el orden de los elementos del array

int arr_srt(Array a,int (*compare)(void*,void*));
//se ordena mediante el metodo burbuja de mayor a menor

void arr_prt(Array array, void (*print)(void*));
//imprimimos todos los elementos del array

