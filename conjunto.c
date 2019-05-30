#include "conjunto.h"
#include <stdlib.h>

#define VIAS 4
#define ERROR 100

void conjunto_crear(conjunto_t* c){
	c->contador = 1;
	for (int i = 0; i < VIAS; ++i){
		bloque_crear((c->bloques + i));
	}
}

unsigned int conjunto_mas_viejo(conjunto_t* c){
	for (int i = 0; i < 4; ++i){
		if(c->bloques[i].orden == 1){
			return i;
		}
	}
	return ERROR;
}

void conjunto_leer(conjunto_t* c, unsigned char* memoria, unsigned int way, unsigned int blocknum){
	bloque_leer(c->bloques + way, blocknum * 64, memoria);
	c->bloques[way].orden = c->contador;
	c->contador++;
	if (c->contador == 6){
		for(int i = 0; i < 4; ++i){
			c->bloques[i].orden--;
		}
		c->contador--;
	}
}

unsigned char conjunto_leer_byte(conjunto_t* c, unsigned char* memoria, unsigned int address, unsigned int offset){
	unsigned int tag = address >> 9;
	for (int i = 0; i < 4; ++i){
		if (c->bloques[i].valido && c->bloques[i].tag == tag){
			return bloque_read_byte(c->bloques + i, offset);
		}
	}
	for (int i = 0; i < 4; ++i){
		if (!(c->bloques[i].valido)){
			conjunto_leer(c, memoria, i, (address - offset) / 64);
			return bloque_read_byte(c->bloques + i, offset);
		}
	}
	unsigned int oldest = conjunto_mas_viejo(c);
	conjunto_leer(c, memoria, oldest, (address - offset) / 64);
	return bloque_read_byte(c->bloques + oldest, offset);
}
