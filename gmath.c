#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gmath.h"
#include "matrix.h"
#include "ml6.h"
#include "symtab.h"
#include "material.h"

/*============================================
  IMPORANT NOTE

  Ambient light is represeneted by a color value

  Point light sources are 2D arrays of doubles.
       - The fist index (LOCATION) represents the vector to the light.
       - The second index (COLOR) represents the color.

  Reflection constants (ka, kd, ks) are represened as arrays of
  doubles (red, green, blue)
  ============================================*/


//lighting functions
color get_lighting( double *normal, double *view, color alight, struct material* mat, double u, double v) {

  color a, d, s, i;
  //normalize(normal);
  double light[2][3];

  i.red = 0;
  i.green = 0;
  i.blue = 0;

  a = calculate_ambient( alight, mat, u, v);

  i.red += a.red;
  i.green += a.green;
  i.blue += a.blue;

  for(int n = 0; n < lastsym; n++){

    if(symtab[n].type == SYM_LIGHT){

      light[LOCATION][0] = symtab[n].s.l->l[0];
      light[LOCATION][1] = symtab[n].s.l->l[1];
      light[LOCATION][2] = symtab[n].s.l->l[2];

      normalize(light[LOCATION]);
      //printf("%f %f %f\n\n", light[LOCATION][0], light[LOCATION][1], light[LOCATION][2]);

      light[COLOR][RED] = symtab[n].s.l->c[RED];
      light[COLOR][GREEN] = symtab[n].s.l->c[GREEN];
      light[COLOR][BLUE] = symtab[n].s.l->c[BLUE];

      d = calculate_diffuse( light, mat, normal, u, v);
      s = calculate_specular( light, mat, view, normal, u, v);

      //printf("%d %d %d\t %d %d %d\n", d.red, d.green, d.blue, s.red, s.green, s.blue);

      i.red += d.red + s.red;
      i.green += d.green + s.green;
      i.blue += d.blue + s.blue;

      //printf("%lf %lf %lf %lf %lf %lf\n", light[LOCATION][0], light[LOCATION][1], light[LOCATION][2], light[COLOR][0], light[COLOR][1], light[COLOR][2]);

      limit_color(&i);
    }
  }

  //printf("%d %d %d\n", i.red,i.green,i.blue);

  limit_color(&i);

  return i;
}

color calculate_ambient(color alight, struct material* mat, double u, double v) {
  color a;
  color t;
  int uLoc, vLoc;

  if(mat->map_ka != NULL){
    uLoc = (int)(u * mat->map_ka_cols);
    vLoc = (int)(v * mat->map_ka_rows);

    if(uLoc >= mat->map_ka_cols) uLoc = mat->map_ka_cols - 1;
    if(vLoc >= mat->map_ka_rows) vLoc = mat->map_ka_rows - 1;
    if(uLoc < 0) uLoc = 0;
    if(vLoc < 0) vLoc = 0;

    t.red = mat->map_ka_raw[uLoc][vLoc].red;
    t.green = mat->map_ka_raw[uLoc][vLoc].green;
    t.blue = mat->map_ka_raw[uLoc][vLoc].blue;
    //printf("%d %d %d\n", t.red, t.green, t.blue);
    a.red = t.red < alight.red ? t.red * mat->ka[0] : alight.red * mat->ka[0];
    a.green = t.green < alight.green ? t.green * mat->ka[1] : alight.green * mat->ka[1];
    a.blue = t.blue < alight.blue ? t.blue * mat->ka[2] : alight.blue * mat->ka[2];
  } else {

    a.red = alight.red * mat->ka[0];
    a.green = alight.green * mat->ka[1];
    a.blue = alight.blue * mat->ka[2];
  }

  return a;
}

color calculate_diffuse(double light[2][3], struct material* mat, double *normal, double u, double v) {
  color d;
  color t;
  double dot;
  int uLoc, vLoc;
  double lvector[3];

  lvector[0] = light[LOCATION][0];
  lvector[1] = light[LOCATION][1];
  lvector[2] = light[LOCATION][2];

  dot = dot_product(normal, lvector);

  if(mat->map_kd != NULL && u >= 0 && v >= 0){
    uLoc = (int)(u * mat->map_kd_cols);
    vLoc = (int)(v * mat->map_kd_rows);

    if(uLoc == mat->map_kd_cols) uLoc--;
    if(vLoc == mat->map_kd_rows) vLoc--;

    t.red = mat->map_kd_raw[uLoc][vLoc].red;
    t.green = mat->map_kd_raw[uLoc][vLoc].green;
    t.blue = mat->map_kd_raw[uLoc][vLoc].blue;
    //printf("%d %d %d %d %d\n", uLoc, vLoc, t.red, t.green, t.blue);

    d.red = t.red < (int)light[COLOR][RED] ? (int)t.red * mat->kd[RED] * dot : (int)light[COLOR][RED] * mat->kd[RED] * dot;
    d.green = t.green < (int)light[COLOR][GREEN] ? (int)t.green * mat->kd[GREEN] * dot : (int)light[COLOR][GREEN] * mat->kd[GREEN] * dot;
    d.blue = t.blue < (int)light[COLOR][BLUE] ? (int)t.blue * mat->kd[BLUE] * dot : (int)light[COLOR][BLUE] * mat->kd[BLUE] * dot;
    //printf("%d %d %d\n", d.red, d.green, d.blue);

  } else {
    d.red = (int)light[COLOR][RED] * mat->kd[RED] * dot;
    d.green = (int)light[COLOR][GREEN] * mat->kd[GREEN] * dot;
    d.blue = (int)light[COLOR][BLUE] * mat->kd[BLUE] * dot;
  }

  

  return d;
  
}

color calculate_specular(double light[2][3], struct material *mat, double *view, double *normal, double u, double v) {
  color s;
  double lvector[3];
  double result;
  double n[3];

  lvector[0] = light[LOCATION][0];
  lvector[1] = light[LOCATION][1];
  lvector[2] = light[LOCATION][2];

  result = 2 * dot_product(normal, lvector);
  n[0] = (normal[0] * result) - lvector[0];
  n[1] = (normal[1] * result) - lvector[1];
  n[2] = (normal[2] * result) - lvector[2];

  result = dot_product(n, view );
  result = result > 0 ? result : 0;
  result = pow( result, mat->ns );

  s.red = (int)(light[COLOR][RED] * mat->ks[0] * result);
  s.green = (int)(light[COLOR][GREEN] * mat->ks[1] * result);
  s.blue = (int)(light[COLOR][BLUE] * mat->ks[2] * result);

  return s;
}

//limit each component of c to a max of 255
void limit_color( color * c ) {
  c->red = c->red > 255 ? 255 : c->red;
  c->green = c->green > 255 ? 255 : c->green;
  c->blue = c->blue > 255 ? 255 : c->blue;

  c->red = c->red < 0 ? 0 : c->red;
  c->green = c->green < 0 ? 0 : c->green;
  c->blue = c->blue < 0 ? 0 : c->blue;
}

//vector functions

double* vector_lerp(double* v0, double* v1, double t){
  double* vf = malloc(sizeof(double) * 3);
  vf[0] = (1 - t)*(v0[0]) + t * v1[0];
  vf[1] = (1 - t)*(v0[1]) + t * v1[1];
  vf[2] = (1 - t)*(v0[2]) + t * v1[2];

  return vf;

}

void set(double* vOld, double* vNew){
  vOld[0] = vNew[0];
  vOld[1] = vNew[1];
  vOld[2] = vNew[2];
}

void add(double* vBase, double* vAdd){
  vBase[0] += vAdd[0];
  vBase[0] += vAdd[0];
  vBase[0] += vAdd[0];
}

void scalar_multiply(double* vector, double s){
  vector[0] *= s;
  vector[1] *= s;
  vector[2] *= s;
}

//normalize vetor, should modify the parameter
void normalize( double *vector ) {
  double magnitude;
  magnitude = sqrt(dot_product(vector,vector));
  magnitude = 1.0/magnitude;
  int i;
  scalar_multiply(vector, magnitude);
}

//Return the dot porduct of a . b
double dot_product( double *a, double *b ) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}


//Calculate the surface normal for the triangle whose first
//point is located at index i in polygons
double *calculate_normal(struct matrix *polygons, int i) {

  double A[3];
  double B[3];
  double *N = (double *)malloc(3 * sizeof(double));

  A[0] = polygons->m[0][i+1] - polygons->m[0][i];
  A[1] = polygons->m[1][i+1] - polygons->m[1][i];
  A[2] = polygons->m[2][i+1] - polygons->m[2][i];

  B[0] = polygons->m[0][i+2] - polygons->m[0][i];
  B[1] = polygons->m[1][i+2] - polygons->m[1][i];
  B[2] = polygons->m[2][i+2] - polygons->m[2][i];

  N[0] = A[1] * B[2] - A[2] * B[1];
  N[1] = A[2] * B[0] - A[0] * B[2];
  N[2] = A[0] * B[1] - A[1] * B[0];

  return N;
}

void print_vertex(double v[3]){
  printf("X: %lf\tY: %lf\tZ: %lf\n", v[0], v[1], v[2]);
}

// double* convert_perspective(double vertex[3], double camera[2][3], double displaySurface[3]){
//   double* finalVals = calloc(2, sizeof(double));

//   double x, y, z, tX, tY, tZ, dx, dy, dz;

//   x = vertex[0]-camera[0][0];
//   y = vertex[1]-camera[0][1];
//   z = vertex[2]-camera[0][2];

//   tX = camera[1][0] * (M_PI / 180);
//   tY = camera[1][1] * (M_PI / 180);
//   tZ = camera[1][2] * (M_PI / 180); 

//   dx = cos(tY) * ( sin(tZ) * y + cos(tZ) * x) - (sin(tY) * z);
//   dy = sin(tX) * ( cos(tY) * z + sin(tY) * (sin(tZ) * y + cos(tZ) * x)) + cos(tX) * (cos(tZ) * y - sin(tZ) * x);
//   dz = cos(tX) * ( cos(tY) * z + sin(tY) * (sin(tZ) * y + cos(tZ) * x)) - sin(tX) * (cos(tZ) * y - sin(tZ) * x);

//   finalVals[0] = (dx * XRES)/(dz * displaySurface[0] * displaySurface[2]);
//   finalVals[1] = (dy * YRES)/(dz * displaySurface[1] * displaySurface[2]);

//   return finalVals;

// }

void convert_perspective(struct matrix* polygons, int i, double f){
  double final[3];

  double vertex[3] = {polygons->m[0][i],polygons->m[1][i],polygons->m[2][i]};

  final[2] = vertex[2] / f;

  final[0] = vertex[0] * final[2];
  final[1] = vertex[1] * final[2];
  final[2] = vertex[2];

  print_vertex(final);

  for(int n = 0; n < 3; n++){
    polygons->m[n][i] = final[n];
  }
  polygons->m[0][i] += XRES/2;
  polygons->m[1][i] += YRES/2;

}