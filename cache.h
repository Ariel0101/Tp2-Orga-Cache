#ifndef CACHE_H
#define CACHE_H
#include "conjunto.h"

#define CONJUNTOS 8
/*La memoria a simular es una cache asociativa por conjuntos de cuatro
vı́as, de 2KB de capacidad, bloques de 64 bytes, polı́tica de reemplazo FIFO
y polı́tica de escritura WT/¬WA. Se asume que el espacio de direcciones es de 16 bits,
y hay entonces una memoria principal a simular con un tamaño de
64KB. Estas memorias pueden ser implementadas como variables globales.
Cada bloque de la memoria caché deberá contar con su metadata, incluyendo
el tag, el bit V y la información necesaria para implementar la polı́tica de
reemplazo FIFO.*/

typedef struct Cache{
	unsigned char* memoria_principal;
	unsigned int accesos;
	unsigned int misses;
	bloque_t** conjuntos;
	int* contadores;
} cache_t;


void cache_crear(cache_t* c, unsigned char* memoria);
/*
Inicializa la memoria principal simulada en
0, los bloques de la caché como inválidos y la tasa de misses a 0.
*/
void init(cache_t* c);

/*
Devuelve el off-set del byte del bloque de memoria al que mapea
la dirección address.
*/
unsigned int get_offset (cache_t* c, unsigned int address);

/*
Devuelve el conjunto de caché al que mapea la dirección address.
*/
unsigned int find_set(cache_t* c, unsigned int address);

/*
Devuelve la vı́a en la que está el bloque más “viejo”
dentro de un conjunto, utilizando el campo corres-
pondiente de los metadatos de los bloques del conjunto.
*/
unsigned int select_oldest(cache_t* c, unsigned int setnum);

/*
Lee el bloque blocknum de memoria
y lo guardar en el conjunto y vı́a indicados en la memoria caché.
*/
void read_tocache(cache_t* c, unsigned int blocknum, unsigned int way, unsigned int set);


void write_tocache(cache_t* c, unsigned int address, unsigned char value);

/*
La función read byte (unsigned int address) debe buscar el valor
del byte correspondiente a la posición address en la caché; si éste no
se encuentra en la caché debe cargar ese bloque. El valor de retorno
siempre debe ser el valor del byte almacenado en la dirección indicada.
*/
unsigned char read_byte(cache_t* c, unsigned int address);

/*
La función write byte(unsigned int address, unsigned char
value) debe escribir el valor value en la posición address de memo-
ria, y en la posición correcta del bloque que corresponde a address,
si el bloque se encuentra en la caché. Si no se encuentra, debe escribir
el valor solamente en la memoria.
*/
void write_byte(cache_t* c, unsigned int address, unsigned char value);

/*
La función get miss rate() debe devolver el porcentaje de misses
desde que se inicializó la caché.
*/
float get_miss_rate(cache_t* c);

void cache_destruir(cache_t* c);

#endif //CACHE_H

