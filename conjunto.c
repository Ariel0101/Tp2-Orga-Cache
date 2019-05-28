#include "conjunto.h"
#include <stdlib.h>

#define VIAS 4

void conjunto_crear(conjunto_t* c){
	for (int i = 0; i < VIAS; ++i){
		bloque_crear((c->bloques + i));
	}
}
