
#ifndef DRAW_H
#define DRAW_H

#include "matrix.h"
#include "ml6.h"
#include "symtab.h"
#include "kdTree.h"
#include "material.h"

#define SHADER_FLAT 0
#define SHADER_GOURAUD 1
#define SHADER_PHONG 2
#define SHADER_WIREFRAME 3

void draw_scanline_gouraud(int x0, double z0, int x1, double z1, int y, 
  screen s, zbuffer zb, color c0, color c1);
void scanline_convert_gouraud( struct matrix *points, struct matrix *textures, 
  int i, screen s, zbuffer zb, struct kdTree* kd, struct material* mat);
void draw_scanline_phong(int x0, double z0, int x1, double z1, int y, 
  double u0, double u1, double v0, double v1, 
  screen s, zbuffer zb, double* vec0, double* vec1,
  double* view, color ambient, struct material* mat);
void scanline_convert_phong( struct matrix *points, struct matrix* textures, 
  int i, screen s, zbuffer zb, struct kdTree* kd,
  double* view, color ambient, struct material* mat);
void draw_scanline_flat(int x0, double z0, int x1, double z1, int y, 
  double u0, double u1, double v0, double v1, 
  struct material* mat, screen s, zbuffer zb, color c);
void scanline_convert_flat( struct matrix* points, struct matrix* textures, 
  int i, screen s, zbuffer zb, double* view, color ambient, struct material* mat, double sNormal[3]);
void draw_wireframe(struct matrix* points, int i, screen s, zbuffer zb, color c);

//polygon organization
void add_polygons( struct matrix * polys,
                   double x0, double y0, double z0,
                   double x1, double y1, double z1,
                   double x2, double y2, double z2);
struct kdTree* compute_vertex_normals(struct matrix* polygons);
void draw_polygons( struct matrix * polys, struct matrix* textures,
                    struct kdTree* kd,
                    screen s, zbuffer zb,
                    double *view, color ambient,
                    int shaderType);

struct matrix* stlConvert(struct matrix* m, char* fileName);

//advanced shapes
//3d shapes
void add_box( struct matrix * edges, struct matrix* textures,
              double matID,
              double x, double y, double z,
              double width, double height, double depth );
void add_plane( struct matrix * edges,
  double x, double y, double z,
  double width, double height);
void add_sphere( struct matrix * edges, struct matrix* textures,
                  double matID,
                 double cx, double cy, double cz,
                 double r, int step );
struct matrix * generate_sphere(double cx, double cy, double cz,
                                double r, int step );
void add_torus( struct matrix * edges, struct matrix* textures,
                double matID,
                double cx, double cy, double cz,
                double r1, double r2, int step );
struct matrix * generate_torus( double cx, double cy, double cz,
                                double r1, double r2, int step );
void add_cylinder( struct matrix* edges, struct matrix* textures,
  double matID,
  double cx, double cy, double cz,
  double r, double h, int step);
struct matrix * generate_cylinder( double cx, double cy, double cz,
  double r, double h, int step);
//2D Curves
void add_circle( struct matrix * points,
                 double cx, double cy, double cz,
                 double r, int step );
void add_curve( struct matrix *points,
                double x0, double y0,
                double x1, double y1,
                double x2, double y2,
                double x3, double y3,
                int step, int type );

void add_point( struct matrix * points, double x, double y, double z);
void add_edge( struct matrix * points,
               double x0, double y0, double z0,
               double x1, double y1, double z1);
void draw_lines( struct matrix * points, screen s, zbuffer zb, color c);
void draw_line(int x0, int y0, double z0,
               int x1, int y1, double z1,
               screen s, zbuffer zb, color c);

#endif
