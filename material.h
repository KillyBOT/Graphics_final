#ifndef MATERIAL_H
#define MATERIAL_H

#include "uthash.h"
#include "matrix.h"
#include "ml6.h"

struct material{
	char *name;
	double ka[3];
	double kd[3];
	double ks[3];
	double ns;
	//double Tr;
	double tf[3];
	//double Ni;
	int illum;

	char *map_kd;
	color** map_kd_raw;
	int map_kd_rows;
	int map_kd_cols;

	// char map_Kd[128];
	// char map_Ns[128];
	// char map_d[128];
	// char map_bump[128];

	UT_hash_handle hh;
};

struct material* m;

void add_material(char *name);
struct material* find_material(char *name);
void delete_material(char* name);
void delete_material_all();
void print_materials();

#endif