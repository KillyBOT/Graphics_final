/*==========================================
  A matrix will be a 4xN array of doubles
  Each column will represent an [x, y, z, 1] point.
  For multiplication purposes, consider the rows like so:
  x0  x1      xn
  y0  y1      yn
  z0  z1  ... zn
  1  1        1
  ==========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*======== struct matrix * make_bezier() ==========
  Returns: The correct 4x4 matrix that can be used
  to generate the coefiecients for a bezier curve
  ====================*/
struct matrix * make_bezier() {
    struct matrix *bm = new_matrix(4, 4);
  bm->lastcol = 4;
  bm->m[0][0] = -1;
  bm->m[0][1] = 3;
  bm->m[0][2] = -3;
  bm->m[0][3] = 1;

  bm->m[1][0] = 3;
  bm->m[1][1] = -6;
  bm->m[1][2] = 3;
  bm->m[1][3] = 0;

  bm->m[2][0] = -3;
  bm->m[2][1] = 3;
  bm->m[2][2] = 0;
  bm->m[2][3] = 0;

  bm->m[3][0] = 1;
  bm->m[3][1] = 0;
  bm->m[3][2] = 0;
  bm->m[3][3] = 0;

  return bm;
}

/*======== struct matrix * make_hermite() ==========
  Returns: The correct 4x4 matrix that can be used
  to generae the coefiecients for a hermite curve
  ====================*/
struct matrix * make_hermite() {
   struct matrix *bm = new_matrix(4, 4);
  bm->lastcol = 4;
  bm->m[0][0] = 2;
  bm->m[0][1] = -2;
  bm->m[0][2] = 1;
  bm->m[0][3] = 1;

  bm->m[1][0] = -3;
  bm->m[1][1] = 3;
  bm->m[1][2] = -2;
  bm->m[1][3] = -1;

  bm->m[2][0] = 0;
  bm->m[2][1] = 0;
  bm->m[2][2] = 1;
  bm->m[2][3] = 0;

  bm->m[3][0] = 1;
  bm->m[3][1] = 0;
  bm->m[3][2] = 0;
  bm->m[3][3] = 0;

  return bm;
}

/*======== struct matrix * generate_curve_coefs() ==========
  Inputs:   double p1
            double p2
            double p3
            double p4
            int type
  Returns:
  A matrix containing the values for a, b, c and d of the
  equation at^3 + bt^2 + ct + d for the curve defined
  by p1, p2, p3 and p4.

  Type determines whether the curve is bezier or hermite (see matrix.h)
  ====================*/
struct matrix * generate_curve_coefs( double p0, double p1,
                                      double p2, double p3, int type) {
    struct matrix *curve;
  struct matrix *coefs = new_matrix(4, 1);

  coefs->lastcol = 1;
  coefs->m[0][0] = p0;
  coefs->m[1][0] = p1;
  coefs->m[2][0] = p2;
  coefs->m[3][0] = p3;

  //  print_matrix(coefs);
  //printf("\n");
  
  if (type == HERMITE)
    curve = make_hermite(); 
  else
    curve = make_bezier();
  
  matrix_mult(curve, coefs);
  free_matrix(curve);

  return coefs;
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
  struct matrix *t = new_matrix(4, 4);
  ident(t);
  t->m[0][3] = x;
  t->m[1][3] = y;
  t->m[2][3] = z;
  return t;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
  struct matrix *t = new_matrix(4, 4);
  ident(t);
  t->m[0][0] = x;
  t->m[1][1] = y;
  t->m[2][2] = z;

  return t;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  struct matrix *t = new_matrix(4, 4);
  ident(t);

  t->m[1][1] = cos(theta);
  t->m[1][2] = -1 * sin(theta);
  t->m[2][1] = sin(theta);
  t->m[2][2] = cos(theta);
  
  return t;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta
         char c 
Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  struct matrix *t = new_matrix(4, 4);
  ident(t);
  
  t->m[0][0] = cos(theta);
  t->m[2][0] = -1 * sin(theta);
  t->m[0][2] = sin(theta);
  t->m[2][2] = cos(theta);

  return t;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta
         char c 
Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  struct matrix *t = new_matrix(4, 4);
  ident(t);
  
  t->m[0][0] = cos(theta);
  t->m[0][1] = -1 * sin(theta);
  t->m[1][0] = sin(theta);
  t->m[1][1] = cos(theta);

  return t;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 

print the matrix such that it looks like
the template in the top comment
*/
void print_matrix(struct matrix *m) {

  int r, c;
  for (r=0; r < m->rows; r++) {
    for (c=0; c < m->lastcol; c++) 
      printf("%0.2f ", m->m[r][c]);
    printf("\n");
  }
  printf("\n");
}//end print_matrix

void print_matrix_point(struct matrix *m, int i){
  if(i < m->lastcol && i >= 0){
    printf("Column %d: %f %f %f\n", i, m->m[0][i], m->m[1][i], m->m[2][i]);
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int r, c;
  
  for (r=0; r < m->rows; r++) 
    for (c=0; c < m->cols; c++) 
      if ( r == c )
	m->m[r][c] = 1;
      else
	m->m[r][c] = 0;
  m->lastcol = m->cols;
}//end ident


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b

multiply a by b, modifying b to be the product
a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  int r, c;
  struct matrix *tmp;
  tmp = new_matrix(4, 1);
  
  for (c=0; c < b->lastcol; c++) {

    //copy current col (point) to tmp
    for (r=0; r < b->rows; r++)      
      tmp->m[r][0] = b->m[r][c];
    
    for (r=0; r < b->rows; r++) 
      b->m[r][c] = a->m[r][0] * tmp->m[0][0] +
	a->m[r][1] * tmp->m[1][0] +
	a->m[r][2] * tmp->m[2][0] +
	a->m[r][3] * tmp->m[3][0];
  }
  free_matrix(tmp);
}//end matrix_mult


/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of columns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  //printf("%d %d %d\n", m->rows, m->cols, newcols);
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
      //printf("Test\n");
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;
  b->lastcol = a->lastcol;
  if(b->cols < a->cols) grow_matrix(b, a->cols);

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}

double matrix_det(struct matrix* m){

  if(m->rows > 4 || m->cols > 4 || m->rows < 2 || m->cols < 2){
    printf("Error! I was too lazy to program in a way to do nxn determinants so you\'re stuck with this.\n");
    return 0;

  } else if (m->rows == 2 && m->cols == 2){
    return (m->m[1][1] * m->m[0][0]) - (m->m[1][0] * m->m[0][1]);
  }

  else {

    double sign = 1;
    double currentTop = 0;
    double final = 0;
    struct matrix* tmp;
    int colToAdd = 0;

    tmp = new_matrix(m->rows-1,m->cols-1);

    for(int top = 0; top < m->cols; top++){

      currentTop = m->m[0][top];

      for(int currentCol = 0; currentCol < m->cols; currentCol++){
        if(currentCol != top){

          for(int currentRow = 1; currentRow < m->rows; currentRow++){
            tmp->m[currentRow-1][colToAdd] = m->m[currentRow][currentCol];
          }

          colToAdd++;
          tmp->lastcol++;
        }
      }

      final += sign * currentTop * matrix_det(tmp);
      sign *= -1;
      tmp->lastcol = 0;
      colToAdd = 0;

    }
    free_matrix(tmp);

    return final;
  }
}

struct matrix* matrix_minor(struct matrix* m){

  //print_matrix(m);
  struct matrix* final = new_matrix(m->rows, m->cols);
  copy_matrix(m,final);
  struct matrix* tmp = new_matrix(m->rows-1,m->cols-1);
  tmp->lastcol = m->cols-1;

  int tmpRow;
  int tmpCol;

  for(int excludeRow = 0; excludeRow < m->rows; excludeRow++){
    for(int excludeCol = 0; excludeCol < m->cols; excludeCol++){

      tmpRow = 0;
      tmpCol = 0;

      for(int r = 0; r < m->rows; r++){

        if(r != excludeRow){
          tmpCol = 0;
          for(int c = 0; c < m->cols; c++){
            if(r != excludeRow && c != excludeCol){
              tmp->m[tmpRow][tmpCol] = m->m[r][c];
              tmpCol++;
            }
          }
          tmpRow++;
        }
        
      }
      //print_matrix(tmp);
      //printf("%lf\n\n", matrix_det(tmp));
      final->m[excludeRow][excludeCol] = pow(-1,excludeRow+1+excludeCol+1)*matrix_det(tmp);

    }
  }

  free_matrix(tmp);

  //print_matrix(final);

  return final;
}

struct matrix* matrix_transpose(struct matrix* m){
  struct matrix* mt = new_matrix(m->cols,m->rows);
  mt->lastcol = m->rows;

  for(int r = 0; r < m->rows; r++){
    for(int c = 0; c < m->cols; c++){
      mt->m[c][r] = m->m[r][c];
    }
  }

  return mt;
}

struct matrix* matrix_adjugate(struct matrix* m){
  struct matrix* minor = matrix_minor(m);

  struct matrix* final = matrix_transpose(minor);

  //print_matrix(final);

  free_matrix(minor);

  return final;
}

struct matrix* matrix_inverse(struct matrix* m){
  //print_matrix(m);
  struct matrix* inverse = matrix_adjugate(m);
  //print_matrix(inverse);

  double det = matrix_det(m);
  det = 1.0 / det;

  for(int r = 0; r < m->rows; r++){
    for(int c = 0; c < m->cols; c++){
      inverse->m[r][c] *= det;
    }
  }

  //print_matrix(inverse);

  return inverse;
}