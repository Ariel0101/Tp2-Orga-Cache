#include "cache.h"
#include <stdlib.h>

#define CONJUNTOS 8
#define VIAS 4

#define ERROR 5

#define MEMORIA 65536

#define MAX_OFFSET 63
#define MAX_IDX 7
#define BITS_OFFSET 6

/*
[			TAG			|	Idx   |    offset    ]
             ^               ^           ^
		  7 bits          3 bits       6 bits
*/
void cache_crear(cache_t* c, unsigned char* memoria){
	c->memoria_principal = memoria;
	c->accesos = 0;
	c->misses = 0;
	c->contadores = (int*) malloc(CONJUNTOS * sizeof(int));
	for (int i = 0; i < CONJUNTOS; ++i){
		c->contadores[i] = 1;
	}
	c->conjuntos = (bloque_t**) malloc(CONJUNTOS * sizeof(bloque_t*));
	for (int i = 0; i < CONJUNTOS; ++i){
		c->conjuntos[i] = (bloque_t*) malloc(VIAS * sizeof(bloque_t));
		for (int j = 0; j < VIAS; ++j){
			bloque_crear(&(c->conjuntos[i][j]));
		}
	}
}

void init(cache_t* c){
	c->accesos = 0;
	c->misses = 0;
	for (int i = 0; i < MEMORIA; ++i){
		c->memoria_principal[i] = 0x00;
	}
	for (int i = 0; i < CONJUNTOS; ++i){
		c->contadores[i] = 1;
	}
	for (int i = 0; i < CONJUNTOS; ++i){
		for (int j = 0; j < VIAS; ++j){
			bloque_reset(&(c->conjuntos[i][j]));
		}
	}
}

unsigned int get_offset (cache_t* c, unsigned int address){
	return address & MAX_OFFSET;
}

unsigned int find_set(cache_t* c, unsigned int address){
	return (address >> BITS_OFFSET) & MAX_IDX;
}

unsigned int select_oldest(cache_t* c, unsigned int setnum){
	for (int i = 0; i < 4; ++i){
		if(c->conjuntos[setnum][i].orden == 1){
			return i;
		}
	}
	return ERROR;
}

void read_tocache(cache_t* c, unsigned int blocknum, unsigned int way, unsigned int set){
	bloque_leer(&(c->conjuntos[set][way]), blocknum, c->memoria_principal);
}

void write_tocache(cache_t* c, unsigned int address, unsigned char value){}

unsigned char read_byte(cache_t* c, unsigned int address){
	c->accesos++;
	unsigned int set = find_set(c, address);
	unsigned int off = get_offset(c, address);
	unsigned int tag = address >> 9;
	//=================================HIT=================================
	for (int i = 0; i < VIAS; ++i){
		if (c->conjuntos[set][i].valido && c->conjuntos[set][i].tag == tag){
			return bloque_read_byte(&(c->conjuntos[set][i]), off);
		}
	}
	c->misses++;
	//========================Buscando bloque vacio========================
	for (int i = 0; i < VIAS; ++i){
		if (!(c->conjuntos[set][i].valido)){
			read_tocache(c, (address - off) / 64, i, set);
			c->conjuntos[set][i].orden = c->contadores[set];
			c->contadores[set]++;
			return bloque_read_byte(&(c->conjuntos[set][i]), off);
		}
	}
	//=====================Reemplazando bloque (FIFO)=====================
	unsigned int oldest = select_oldest(c, set);
	read_tocache(c, (address - off) / 64, oldest, set);
	c->conjuntos[set][oldest].orden = c->contadores[set];
	for (int i = 0; i < VIAS; ++i){
		c->conjuntos[set][i].orden--;
	}
	return bloque_read_byte(&(c->conjuntos[set][oldest]), off);

}

void write_byte(cache_t* c, unsigned int address, unsigned char value){
	c->accesos++;
	unsigned int set = find_set(c, address);
	unsigned int off = get_offset(c, address);
	unsigned int tag = address >> 9;
	for (int i = 0; i < VIAS; ++i){
		if (c->conjuntos[set][i].valido && c->conjuntos[set][i].tag == tag){
			bloque_write_byte(&(c->conjuntos[set][i]), off, value);
			c->memoria_principal[address] = value;
			return;
		}
	}
	c->misses++;
	c->memoria_principal[address] = value;
}
#include <stdio.h>
float get_miss_rate(cache_t* c){
	return ((float)c->misses / (float)c->accesos);
}

void cache_destruir(cache_t* c){
	free(c->contadores);

	for (int i = 0; i < CONJUNTOS; ++i){
		for (int j = 0; j < VIAS; ++j){
			bloque_destruir(&(c->conjuntos[i][j]));
		}
		free(c->conjuntos[i]);
	}
	free(c->conjuntos);
}