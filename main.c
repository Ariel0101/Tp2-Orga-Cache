#include "cache.h"
#include <stdio.h>
/*
Compilar: gcc -o tp cache.c main.c bloque.c conjunto.c
*/
int main(){
	cache_t cache;
	char* pruebas = "EXITO";
	//Prueba get offset
	unsigned int off;
	for (unsigned int prueba = 0; prueba != 2048; prueba++){
		off = get_offset(&cache, prueba);
		if (off != (prueba % 64)){
			pruebas = "ERROR";
		}
	}

	printf("Prueba get offset: %s\n", pruebas);

	//Prueba find_set
	
	unsigned int idx;
	for (unsigned int prueba = 0; prueba < 64; prueba++){
		idx = find_set(&cache, prueba);
		if (idx != 0){
			pruebas = "ERROR";
		}
	}
	for (unsigned int prueba = 64; prueba < 2*64; prueba++){
		idx = find_set(&cache, prueba);
		if (idx != 1){
			pruebas = "ERROR";
		}
	}
	for (unsigned int prueba = 2*64; prueba < 3*64; prueba++){
		idx = find_set(&cache, prueba);
		if (idx != 2){
			pruebas = "ERROR";
		}
	}

	printf("Prueba find set: %s\n", pruebas);
	return 0;
}