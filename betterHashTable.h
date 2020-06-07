#ifndef BETTERHASHTABLE_H
#define BETTERHASHTABLE_H

#include "ml6.h"

struct vertex {
	double x,y,z;
}

struct hashTable {
	struct vertex v;
	struct vertex n;
	color c;

	UT_hash_handle hh;
}

void set_normal(struct hashTable* h, double vertex[3], double normal[3]);
struct hashTable *get_element(struct hashTable* h, double vertex[3]);
double *get_normal(struct hashTable* h, double vertex[3]);
void print_hashTable(struct hashTable* h);
void delete_hashTable(struct hashTable* h);

#endif