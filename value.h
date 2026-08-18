// VALUE: Solo contiene una funcion que copia un valor de cada tipo en otro

// Metodos

#define cast(T,V) *((T*)V) //hace cast de un valor en void a un tipo T

// Tipos

typedef unsigned char uchar;

// Funciones

int val_cpy(void* d,void* o,uchar size);
//copia el valor o en d, size indica los bytes que se copiaran
