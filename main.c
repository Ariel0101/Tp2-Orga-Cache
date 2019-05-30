#include "cache.h"
#include <stdio.h>

/*
Compilar: gcc -o tp cache.c main.c bloque.c conjunto.c
*/
int main(){
	unsigned char memoria[64 * 2];
	for (int i = 0; i < 64 * 2; ++i){
		memoria[i] = 'a';
	}
	conjunto_t conj;
	conjunto_crear(&conj);

	conjunto_leer(&conj, 0, memoria);
	printf("%s\n", conj.bloques[0].espacio);
	return 0;
}