#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "betterHashTable.h"
#include "ml6.h"
#include "matrix.h"

void set_normal(struct hashTable* h, double vertex[3], double normal[3]){
	struct hashTable desired, *element;

	memset(&desired,0,sizeof(struct vertex));
	desired.v.x=vertex[0];
	desired.v.y=vertex[1];
	desired.v.z=vertex[2];

	HASH_FIND(hh, h, &desired.v, sizeof(struct vertex), element);

	if(element){
		
	}
}
struct hashTable *get_element(struct hashTable* h, double vertex[3]);
double *get_normal(struct hashTable* h, double vertex[3]);
void print_hashTable(struct hashTable* h);
void delete_hashTable(struct hashTable* h);