#include "cache.h"
#include <stdlib.h>

#define CONJUNTOS 8

#define MAX_OFFSET 63
#define MAX_IDX 7
#define BITS_OFFSET 6

/*
[			TAG			|	Idx   |    offset    ]
             ^               ^           ^
		  7 bits          3 bits       6 bits
*/

void cache_crear(cache_t* c, char* memoria){
	c->memoria_principal = memoria;
	for (int i = 0; i < CONJUNTOS; ++i){
		conjunto_crear((c->conjuntos + i));
	} 
}

void init(cache_t* c){
}

unsigned int get_offset (cache_t* c, unsigned int address){
	return address & MAX_OFFSET;
}

unsigned int find_set(cache_t* c, unsigned int address){
	return (address >> BITS_OFFSET) & MAX_IDX;
}

unsigned int select_oldest(cache_t* c, unsigned int setnum){
	return conjunto_mas_viejo(c->conjuntos + setnum);
}

void read_tocache(cache_t* c, unsigned int blocknum, unsigned int way, unsigned int set){
	conjunto_leer(c->conjuntos + set, c->memoria_principal, way, blocknum);
}

void write_tocache(cache_t* c, unsigned int address, unsigned char value){
}

unsigned char read_byte(cache_t* c, unsigned int address){
	unsigned int via = find_set(c, address);
	unsigned int off = get_offset(c, address);
	return conjunto_leer_byte(c->conjuntos + via, c->memoria_principal, address, off);
}

void write_byte(cache_t* c, unsigned int address, unsigned char value){
}

float get_miss_rate(cache_t* c){
}
