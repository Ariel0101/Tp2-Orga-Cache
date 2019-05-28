#ifndef BLOQUE_H
#define BLOQUE_H
#include <stdbool.h>

typedef struct Bloque{
	char espacio[64];
	unsigned int tag;
	bool valido;
} bloque_t;

#endif //BLOQUE_H
