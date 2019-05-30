#ifndef CONJUNTO_H
#define CONJUNTO_H
#include "bloque.h"

typedef struct Conjunto{
	bloque_t bloques[4];
	int contador;
} conjunto_t;


void conjunto_crear(conjunto_t* c);

unsigned int conjunto_mas_viejo(conjunto_t* c);

void conjunto_leer(conjunto_t* c, unsigned char* memoria, unsigned int way, unsigned int blocknum);

unsigned char conjunto_leer_byte(conjunto_t* c, unsigned char* memoria, unsigned int address, unsigned int offset);

#endif //CONJUNTO_H
