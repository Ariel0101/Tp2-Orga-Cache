#include "bloque.h"
#include <stdlib.h>

#define BYTES_X_BLOQUE 64

void bloque_crear(bloque_t* b){
	b->espacio = (unsigned char*) malloc(BYTES_X_BLOQUE * sizeof(unsigned char));
	b->tag = 0;
	b->valido = false;
	b->orden = 0;
}

void bloque_reset(bloque_t* b){
	b->tag = 0;
	b->valido = false;
	b->orden = 0;
}

void bloque_leer(bloque_t* b, unsigned int blocknum, unsigned char* memoria){
	unsigned int address = 64 * blocknum;
	for (unsigned int i = 0; i < BYTES_X_BLOQUE; ++i){
		b->espacio[i] = memoria[address + i];
	}
	b->tag = address >> 9;
	b->valido = true;
}

unsigned char bloque_read_byte(bloque_t* b, unsigned int offset){
	return b->espacio[offset];
}

void bloque_write_byte(bloque_t* b, unsigned int offset, unsigned char value){
	b->espacio[offset] = value;
}

void bloque_destruir(bloque_t* b){
	free(b->espacio);
}
