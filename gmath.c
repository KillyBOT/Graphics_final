#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gmath.h"
#include "matrix.h"
#include "ml6.h"
#include "symtab.h"

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
color get_lighting( double *normal, double *view, color alight, struct constants *reflect, double specExp) {

  color a, d, s, i;
  //normalize(normal);
  double light[2][3];

  i.red = 0;
  i.green = 0;
  i.blue = 0;

  a = calculate_ambient( alight, reflect );

  i.red += a.red;
  i.green += a.green;
  i.blue += a.blue;

  for(int n = 0; n < lastsym; n++){

    if(symtab[n].type == SYM_LIGHT){

      light[LOCATION][0] = symtab[n].s.l->l[0];
      light[LOCATION][1] = symtab[n].s.l->l[1];
      light[LOCATION][2] = symtab[n].s.l->l[2];

      normalize(light[LOCATION]);

      light[COLOR][RED] = symtab[n].s.l->c[RED];
      light[COLOR][GREEN] = symtab[n].s.l->c[GREEN];
      light[COLOR][BLUE] = symtab[n].s.l->c[BLUE];

      d = calculate_diffuse( light, reflect, normal );
      s = calculate_specular( light, reflect, view, normal, specExp);

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

color calculate_ambient(color alight, struct constants *reflect ) {
  color a;
  a.red = alight.red * reflect->r[AMBIENT_R];
  a.green = alight.green * reflect->g[AMBIENT_R];
  a.blue = alight.blue * reflect->b[AMBIENT_R];;

  return a;
}

color calculate_diffuse(double light[2][3], struct constants *reflect, double *normal ) {
  color d;
  double dot;
  double lvector[3];

  lvector[0] = light[LOCATION][0];
  lvector[1] = light[LOCATION][1];
  lvector[2] = light[LOCATION][2];

  dot = dot_product(normal, lvector);

  d.red = (int)(light[COLOR][RED] * reflect->r[DIFFUSE_R] * dot);
  d.green = (int)(light[COLOR][GREEN] * reflect->g[DIFFUSE_R] * dot);
  d.blue = (int)(light[COLOR][BLUE] * reflect->b[DIFFUSE_R] * dot);

  return d;
}

color calculate_specular(double light[2][3], struct constants *reflect, double *view, double *normal, double specExp) {
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
  result = pow( result, specExp );

  s.red = (int)(light[COLOR][RED] * reflect->r[SPECULAR_R] * result);
  s.green = (int)(light[COLOR][GREEN] * reflect->g[SPECULAR_R] * result);
  s.blue = (int)(light[COLOR][BLUE] * reflect->b[SPECULAR_R] * result);

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

double* convert_perspective(double vertex[3], double camera[2][3], double displaySurface[3]){
  double* finalVals = calloc(2, sizeof(double));

  double x, y, z, tX, tY, tZ, dx, dy, dz;

  x = vertex[0]-camera[0][0];
  y = vertex[1]-camera[0][1];
  z = vertex[2]-camera[0][2];

  tX = camera[1][0] * (M_PI / 180);
  tY = camera[1][1] * (M_PI / 180);
  tZ = camera[1][2] * (M_PI / 180); 

  dx = cos(tY) * ( sin(tZ) * y + cos(tZ) * x) - (sin(tY) * z);
  dy = sin(tX) * ( cos(tY) * z + sin(tY) * (sin(tZ) * y + cos(tZ) * x)) + cos(tX) * (cos(tZ) * y - sin(tZ) * x);
  dz = cos(tX) * ( cos(tY) * z + sin(tY) * (sin(tZ) * y + cos(tZ) * x)) - sin(tX) * (cos(tZ) * y - sin(tZ) * x);

  finalVals[0] = (dx * XRES)/(dz * displaySurface[0] * displaySurface[2]);
  finalVals[1] = (dy * YRES)/(dz * displaySurface[1] * displaySurface[2]);

  return finalVals;

}

//double* 