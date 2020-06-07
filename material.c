#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "material.h"
#include "uthash.h"

extern struct material* m;
extern struct material_id* mI;
extern int currentID;

void add_material(char *name){


	struct material* new;
	struct material_id* new_id;

	if(find_material(name) == NULL){
		//printf("Creating material %s...\n", name);
		new = (struct material*)malloc(sizeof(struct material));
		new_id = (struct material_id*)malloc(sizeof(struct material_id));

		new->name = strdup(name);
		new->map_kd = NULL;
		new->id = currentID;

		new_id->id = currentID;
		currentID++;
		new_id->mat = strdup(name);

		HASH_ADD_KEYPTR(hh, m, new->name, strlen(new->name), new);
		HASH_ADD_INT(mI, id, new_id);
	}

}
struct material* find_material(char *name){

	struct material* found;

	HASH_FIND_STR(m, name, found);
	//if(found == NULL)printf("Could not find material %s\n", name);

	return found;
}
char* find_material_name(int id){
	struct material_id* found_id;

	HASH_FIND_INT(mI, &id, found_id);
	if(found_id == NULL)printf("Could not find material with id %d\n", id);

	return found_id->mat;

}
void delete_material(char* name){


	struct material* dead;

	dead = find_material(name);

	HASH_DEL(m, dead);
	free(dead);
}
void delete_material_all(){


	struct material *current, *tmp;
	struct material_id *current_id, *tmp_id;

	HASH_ITER(hh, m, current, tmp){
		HASH_DEL(m, current);
		free(current->name);
		if(current->map_kd != NULL){
			free(current->map_kd);
			for(int n = 0; n < current->map_kd_cols; n++){
				free(current->map_kd_raw[n]);
			}
			free(current->map_kd_raw);
		}
		free(current);
	}

	HASH_ITER(hh, mI, current_id, tmp_id){
		HASH_DEL(mI, current_id);
		free(current_id->mat);
	}


}
void print_materials(){

	struct material *current, *tmp;
	printf("Current materials:\n");

	HASH_ITER(hh, m, current, tmp) {
		printf("Name: %s\n", current->name);
		printf("ID: %d\n", current->id);
		printf("Ka: [%lf] [%lf] [%lf]\n", current->ka[0], current->ka[1], current->ka[2]);
		printf("Kd: [%lf] [%lf] [%lf]\n", current->kd[0], current->kd[1], current->kd[2]);
		printf("Ks: [%lf] [%lf] [%lf]\n", current->ks[0], current->ks[1], current->ks[2]);
		printf("Ns: [%lf]\n", current->ns);
		printf("Tf: [%lf] [%lf] [%lf]\n", current->tf[0], current->tf[1], current->tf[2]);
		printf("Illumination Model: %d\n", current->illum);
		if(current->map_kd != NULL) printf("map_Kd: [%s]\n", current->map_kd);

		printf("\n");
	}
}