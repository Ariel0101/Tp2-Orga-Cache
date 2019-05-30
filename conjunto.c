#include "conjunto.h"
#include <stdlib.h>

#define VIAS 4

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
	return 5;
}

void conjunto_leer(conjunto_t* c, unsigned char* memoria, unsigned int way, unsigned int blocknum){
	c->bloques[way].orden = c->contador;
	c->contador++;
	bloque_leer(c->bloques + way, blocknum * 64, memoria);
}

unsigned char conjunto_leer_byte(conjunto_t* c, unsigned int address, unsigned int offset){
	unsigned int tag = address >> 9;
	for (int i = 0; i < 4; ++i){
		if (c->bloques[i].valido && c->bloques[i].tag == tag){
			return bloque_read_byte(offset);
		}
	}

}
