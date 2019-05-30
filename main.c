#include "cache.h"
#include <stdio.h>

/*
Compilar: gcc -o tp cache.c main.c bloque.c conjunto.c
*/
int main(){
	unsigned char memoria[65536];
	int i = 0;
	for (; i < 65536; ++i){
		*(memoria + i) = 'A';
	}

	*(memoria + 15 + 64) = 0x21; //!
	*(memoria + 520 + 64) = 0x28; //(
	*(memoria + 1025 + 64) = 0x2B; //+
	*(memoria + 1541 + 64) = 0x2F; // /
	*(memoria + 2049 + 64) = 0x5E; // ^
	*(memoria + 2563 + 64) = 0x23; // #

	cache_t cache;
	cache_crear(&cache, memoria);


	unsigned char dato1 = read_byte(&cache, 15 + 64);
	unsigned char dato2 = read_byte(&cache, 520+ 64);
	unsigned char dato3 = read_byte(&cache, 1025+ 64);
	unsigned char dato4 = read_byte(&cache, 1541+ 64);

	printf("%s : %d\n", cache.conjuntos[1][0].espacio, cache.conjuntos[1][0].orden);
	printf("%s : %d\n", cache.conjuntos[1][1].espacio, cache.conjuntos[1][1].orden);
	printf("%s : %d\n", cache.conjuntos[1][2].espacio, cache.conjuntos[1][2].orden);
	printf("%s : %d\n", cache.conjuntos[1][3].espacio, cache.conjuntos[1][3].orden);

	printf("%x\n", dato1);
	printf("%x\n", dato2);
	printf("%x\n", dato3);
	printf("%x\n", dato4);

	unsigned char dato6 = read_byte(&cache, 2563+ 64);

	printf("%s : %d\n", cache.conjuntos[1][0].espacio, cache.conjuntos[1][0].orden);
	printf("%s : %d\n", cache.conjuntos[1][1].espacio, cache.conjuntos[1][1].orden);
	printf("%s : %d\n", cache.conjuntos[1][2].espacio, cache.conjuntos[1][2].orden);
	printf("%s : %d\n", cache.conjuntos[1][3].espacio, cache.conjuntos[1][3].orden);

	printf("%x\n", dato6);

	cache_destruir(&cache);

	return 0;
}