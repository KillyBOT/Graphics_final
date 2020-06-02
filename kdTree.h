#ifndef KDTREE_H
#define KDTREE_H

#include "ml6.h"
#include "symtab.h"
#include "matrix.h"

#define MAXDEPTH 3

struct kdNode{
	double vertex[3];
	double normal[3];
	color c;
	struct kdNode* left;
	struct kdNode* right;
};

struct kdTree {
	struct kdNode* root;
	int changed;
	int size;
};

struct kdTree* kdCreate();
void kdFree(struct kdTree* kd);
void kdFree_helper(struct kdNode* k);
struct kdNode* kdNodeCreate(double* vertex, double* normal);
void kdCopy(struct kdTree* dest, struct kdTree* src);
void kdCopy_helper(struct kdNode* k, struct kdTree* dest);

struct kdTree* kdInsert(struct kdTree* kd, double* vertex, double* normal);
struct kdNode* kdInsert_helper(struct kdNode* k, double* vertex, double* normal, int depth);
struct kdNode* kdGetNode(struct kdTree* kd, double* vertex);
struct kdNode* kdGetNode_helper(struct kdNode* k, double* vertex, int depth);
struct kdTree* kdNormalize(struct kdTree* kd, double *view, color ambient, struct constants* reflect);
struct kdNode* kdNormalize_helper(struct kdNode* k, double *view, color ambient, struct constants* reflect);
struct kdTree* kdTransform(struct kdTree* kd, struct matrix* m);
struct kdNode* kdTransform_helper(struct kdNode* k, struct matrix* m, struct matrix* mn);
void kdCheck(struct kdTree* kd, struct matrix* m);
int kdCheck_helper(struct kdNode* k, double* vertex);
double* kdGetNormal(struct kdTree* kd, double* vertex);
color kdGetColor(struct kdTree* kd, double* vertex);

void kdPrint(struct kdTree* kd);
void kdPrint_helper(struct kdNode* k, int depth);

#endif