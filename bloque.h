#ifndef BLOQUE_H
#define BLOQUE_H
#include <stdbool.h>

typedef struct Bloque{
	unsigned char* espacio;
	unsigned int tag;
	bool valido;
	int orden;
} bloque_t;


void bloque_crear(bloque_t* b);

void bloque_leer(bloque_t* b, unsigned int address, unsigned char* memoria);

void bloque_escribir(bloque_t* b, unsigned int address, unsigned char* memoria);


#endif //BLOQUE_H
