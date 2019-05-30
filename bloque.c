#include "bloque.h"
#include <stdlib.h>

#define BYTES_X_BLOQUE 64

void bloque_crear(bloque_t* b){
	b->espacio = (unsigned char*) malloc(BYTES_X_BLOQUE * sizeof(unsigned char));
	b->tag = 0;
	b->valido = false;
	b->libre = true;
	b->orden = 0;
}

void bloque_leer(bloque_t* b, unsigned int address, unsigned char* memoria){
	for (unsigned int i = 0; i < BYTES_X_BLOQUE; ++i){
		b->espacio[i] = memoria[address + i];
	}
	b->tag = address >> 9;
	b->valido = true;
	b->libre = false;
}

void bloque_escribir(bloque_t* b, unsigned int address, unsigned char* memoria){
	for (unsigned int i = 0; i < BYTES_X_BLOQUE; ++i){
		memoria[address + i] = b->espacio[i];
	}
	b->tag = 0;
	b->valido = false;
	b->libre = true;
}


