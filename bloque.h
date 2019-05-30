#ifndef BLOQUE_H
#define BLOQUE_H
#include <stdbool.h>

typedef struct Bloque{
	unsigned char* espacio;
	unsigned int tag;
	bool valido;
	unsigned int orden;
} bloque_t;


void bloque_crear(bloque_t* b);

void bloque_reset(bloque_t* b);

void bloque_leer(bloque_t* b, unsigned int blocknum, unsigned char* memoria);

unsigned char bloque_read_byte(bloque_t* b, unsigned int offset);

void bloque_write_byte(bloque_t* b, unsigned int offset, unsigned char value);

void bloque_destruir(bloque_t* b);


#endif //BLOQUE_H
