#ifndef CONJUNTO_H
#define CONJUNTO_H
#include "bloque.h"

typedef struct Conjunto{
	bloque_t bloques[4];
} conjunto_t;


void conjunto_crear(conjunto_t* c);

#endif //CONJUNTO_H
