#include "cache.h"
#include <stdio.h>
#include <string.h>

#define MAX_CHAR 255
#define _64KB 65536
#define MAX_COMANDO 10
#define E_VALOR "Valor fuera de rango\n"
#define E_COMANDO "Comando erroneo\n"
#define E_DIREC "Direccion fuera de rango\n"

/*
Compilar: gcc -pedantic -Werror -ggdb -o tp cache.c main.c bloque.c
*/
int main(int argc, char** argv){
//=====================Iniciar Cache=====================
	unsigned char memoria[_64KB];
	cache_t cache;
	cache_crear(&cache, memoria);
	init(&cache);
//=========================Parse=========================
	FILE* archivo = fopen(argv[1], "r");
	if (!archivo){
		printf("Error al abrir archivo\n");
		return 0;
	}
	char com[MAX_COMANDO];
	unsigned int dir = 0;
	unsigned int dato = 0;
	int i;
	unsigned char c;
	do{
		i = fscanf(archivo, "%s %u, %u\n", com, &dir, &dato);
		c = (unsigned char) dato;
		if (strcmp(com, "FLUSH") == 0){
			init(&cache);
		} else if(strcmp(com, "R") == 0){
			if (dir > _64KB){
				printf(E_DIREC);
				continue;
			}
			unsigned char res = read_byte(&cache, dir);
			printf("Valor leido: %d\n", res);
		} else if(strcmp(com, "W") == 0){
			if (dato > MAX_CHAR){
				printf(E_VALOR);
				continue;
			}
			if (dir > _64KB){
				printf(E_DIREC);
				continue;
			}
			write_byte(&cache, dir, c);
		} else if(strcmp(com, "MR") == 0){
			float mr = get_miss_rate(&cache);
			printf("%.6f\n", mr);
		} else {
			printf(E_COMANDO);
		}
	} while(!feof(archivo));
	cache_destruir(&cache);
	fclose(archivo);
	return 0;
}