#ifndef GMATH_H
#define GMATH_H

#include "matrix.h"
#include "ml6.h"
#include "symtab.h"
#include "material.h"

// constants for lighting
#define LOCATION 0
#define COLOR 1
#define RED 0
#define GREEN 1
#define BLUE 2


#define SPECULAR_EXP 32

// lighting functions
color get_lighting( double *normal, double *view, color alight, struct material* mat, double u, double v);
color calculate_ambient(color alight, struct material* mat, double u, double v);
color calculate_diffuse(double light[2][3], struct material* mat, double *normal, double u, double v);
color calculate_specular(double light[2][3], struct material* mat, double *view, double *normal, double u, double v);
void limit_color( color * c );

// vector functions
double* vector_lerp(double* v0, double* v1, double t);
void set(double* vOld, double* vNew);
void add(double* vBase, double* vAdd);
void normalize( double *vector );
double dot_product( double *a, double *b );
double *calculate_normal(struct matrix *polygons, int i);
void print_vertex(double v[3]);

//Perspective drawing
double* convert_perspective(double vertex[3], double camera[2][3], double displaySurface[3]);
//double* convert_perspective(double vertex[3], )

#endif
