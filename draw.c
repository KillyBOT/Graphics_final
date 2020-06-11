#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "math.h"
#include "gmath.h"
#include "symtab.h"
#include "kdTree.h"
#include "material.h"

/*======== void draw_scanline() ==========
  Inputs: struct matrix *points
          int i
          screen s
          zbuffer zb
          color c

  Line algorithm specifically for horizontal scanlines
  ====================*/
void draw_scanline_gouraud(int x0, double z0, int x1, double z1, int y, 
  screen s, zbuffer zb, color c0, color c1) {

  int tempX, tempZ;
  color tempC;
  double cR, cG, cB, dcR, dcG, dcB;
  color cF;
  //swap if needed to assure left->right drawing
  if (x0 > x1) {
    tempX = x0;
    tempZ = z0;
    tempC = c0;
    x0 = x1;
    z0 = z1;
    c0 = c1;
    x1 = tempX;
    z1 = tempZ;
    c1 = tempC;
  }

  double delta_z;
  delta_z = (x1 - x0) != 0 ? (z1 - z0) / (x1 - x0 + 1) : 0;
  int x;
  double z = z0;

  cR = c0.red;
  cG = c0.green;
  cB = c0.blue;

  dcR = (x1 - x0 != 0) ? ((double)c1.red-(double)c0.red)/(x1-x0+1) : 0;
  dcG = (x1 - x0 != 0) ? ((double)c1.green-(double)c0.green)/(x1-x0+1) : 0;
  dcB = (x1 - x0 != 0) ? ((double)c1.blue-(double)c0.blue)/(x1-x0+1) : 0;

  for(x=x0; x <= x1; x++) {

    cF.red = (unsigned short)cR;
    cF.green = (unsigned short)cG;
    cF.blue = (unsigned short)cB;

    limit_color(&cF);

    //printf("%d %d %d\n",cF.red,cF.green,cF.blue);

    plot(s, zb, cF, x, y, z);

    z+= delta_z;
    cR += dcR;
    cG += dcG;
    cB += dcB;

  }
}

void draw_scanline_phong(int x0, double z0, int x1, double z1, int y, 
  double u0, double u1, double v0, double v1, 
  screen s, zbuffer zb, double* vec0, double* vec1,
  double* view, color ambient, struct material* mat) {

  int tempX, tempZ;
  double tempU, tempV;
  double u, v;
  double du, dv;
  double v0f[3];
  double v1f[3];
  double vec[3];
  double dVec[3];
  double finalV[3];
  color c;
  //swap if needed to assure left->right drawing
  set(v0f, vec0);
  set(v1f, vec1);
  if (x0 > x1) {
    tempX = x0;
    tempZ = z0;
    tempU = u0;
    tempV = v0;
    x0 = x1;
    z0 = z1;
    u0 = u1;
    v0 = v1;
    x1 = tempX;
    z1 = tempZ;
    u1 = tempU;
    v1 = tempV;
    set(v1f, vec0);
    set(v0f, vec1);
  }

  double delta_z;
  int distance = x1 - x0 + 1;
  delta_z = (x1 - x0) != 0 ? (z1 - z0) / distance : 0;
  int x;
  double z;

  set(vec,v0f);
  u = u0;
  v = v0;
  z = z0;

  dVec[0] = distance != 0 ? (v1f[0] - v0f[0]) / distance : 0;
  dVec[1] = distance != 0 ? (v1f[1] - v0f[1]) / distance : 0;
  dVec[2] = distance != 0 ? (v1f[2] - v0f[2]) / distance : 0;

  du = distance != 0 ? (u1 - u0) / distance : 0;
  dv = distance != 0 ? (v1 - v0) / distance : 0;

  // double* perspectiveView;

  // double camera[2][3];
  // double displaySurface[3];
  // camera[0][0] = view[0];
  // camera[0][1] = view[1];
  // camera[0][2] = 0;

  // //Making up values for now
  // camera[1][0] = 0;
  // camera[1][1] = 0;
  // camera[1][2] = 0;

  // displaySurface[0] = 0.5;
  // displaySurface[1] = 0.5;
  // displaySurface[2] = 3;

  for(x=x0; x <= x1; x++) {

    //normalize(vn);

    c = get_lighting(vec, view, ambient, mat, u, v);
    //printf("u:[%lf]\tv:[%lf]\n", u, v);

    // finalV[0] = x;
    // finalV[1] = y;
    // finalV[2] = z;

    // perspectiveView = convert_perspective(finalV, camera, displaySurface);
    // printf("%d %d %lf %lf\n", x, y, perspectiveView[0], perspectiveView[1]);
    // plot(s, zb, c, (int)perspectiveView[0], (int)perspectiveView[1], z);
    // free(perspectiveView);

    plot(s, zb, c, x, y, z);

    z+= delta_z;
    u += du;
    v += dv;
    vec[0] += dVec[0];
    vec[1] += dVec[1];
    vec[2] += dVec[2];

  }
}

void draw_scanline_flat(int x0, double z0, int x1, double z1, int y, 
  double u0, double u1, double v0, double v1,
  struct material* mat, screen s, zbuffer zb, color c) {

  int tempX, tempZ;
  //swap if needed to assure left->right drawing
  if (x0 > x1) {
    tempX = x0;
    tempZ = z0;
    x0 = x1;
    z0 = z1;
    x1 = tempX;
    z1 = tempZ;
  }

  double delta_z;
  delta_z = (x1 - x0) != 0 ? (z1 - z0) / (x1 - x0 + 1) : 0;
  int x;
  double z = z0;

  for(x=x0; x <= x1; x++) {

    //printf("%d %d %d\n",cF.red,cF.green,cF.blue);

    plot(s, zb, c, x, y, z);

    z+= delta_z;
  }
}
/*======== void scanline_convert() ==========
  Inputs: struct matrix *points
          int i
          screen s
          zbuffer zb
          color il

  Fills in polygon i by drawing consecutive horizontal (or vertical) lines.
  ====================*/
void scanline_convert_gouraud( struct matrix *points, struct matrix* textures,
  int i, screen s, zbuffer zb, struct kdTree* kd, struct material* mat) {

  int top, mid, bot, y;
  double vTop[3], vMid[3], vBot[3];
  // double topN[3], midN[3], botN[3];
  int distance0, distance1, distance2;
  double x0, x1, y0, y1, y2, dx0, dx1, z0, z1, dz0, dz1;
  color iTop, iMid, iBot;
  color c0, c1;
  double c0R, c0G, c0B, c1R, c1G, c1B;
  double dc0R, dc0G, dc0B, dc1R, dc1G, dc1B;
  int flip = 0;

  z0 = z1 = dz0 = dz1 = 0;

  y0 = points->m[1][i];
  y1 = points->m[1][i+1];
  y2 = points->m[1][i+2];

  // Alas random color, we hardly knew ye
  /* color c; */
  /* c.red = (23 * (i/3))%255; */
  /* c.green = (109 * (i/3))%255; */
  /* c.blue = (c.blue+(227 * (i/3)))%255; */

  //find bot, mid, top
  if ( y0 <= y1 && y0 <= y2) {
    bot = i;
    if (y1 <= y2) {
      mid = i+1;
      top = i+2;
    }
    else {
      mid = i+2;
      top = i+1;
    }
  }//end y0 bottom
  else if (y1 <= y0 && y1 <= y2) {
    bot = i+1;
    if (y0 <= y2) {
      mid = i;
      top = i+2;
    }
    else {
      mid = i+2;
      top = i;
    }
  }//end y1 bottom
  else {
    bot = i+2;
    if (y0 <= y1) {
      mid = i;
      top = i+1;
    }
    else {
      mid = i+1;
      top = i;
    }
  }//end y2 bottom
  //printf("ybot: %0.2f, ymid: %0.2f, ytop: %0.2f\n", (points->m[1][bot]),(points->m[1][mid]), (points->m[1][top]));
  /* printf("bot: (%0.2f, %0.2f, %0.2f) mid: (%0.2f, %0.2f, %0.2f) top: (%0.2f, %0.2f, %0.2f)\n", */

  x0 = points->m[0][bot];
  x1 = points->m[0][bot];
  z0 = points->m[2][bot];
  z1 = points->m[2][bot];
  y = (int)(points->m[1][bot]);

  distance0 = (int)(points->m[1][top]) - y + 1;
  distance1 = (int)(points->m[1][mid]) - y + 1;
  distance2 = (int)(points->m[1][top]) - (int)(points->m[1][mid]) + 1;

  dx0 = distance0 > 0 ? (points->m[0][top]-points->m[0][bot])/distance0 : 0;
  dx1 = distance1 > 0 ? (points->m[0][mid]-points->m[0][bot])/distance1 : 0;
  dz0 = distance0 > 0 ? (points->m[2][top]-points->m[2][bot])/distance0 : 0;
  dz1 = distance1 > 0 ? (points->m[2][mid]-points->m[2][bot])/distance1 : 0;

  vTop[0] = points->m[0][top];
  vTop[1] = points->m[1][top];
  vTop[2] = points->m[2][top];

  vMid[0] = points->m[0][mid];
  vMid[1] = points->m[1][mid];
  vMid[2] = points->m[2][mid];

  vBot[0] = points->m[0][bot];
  vBot[1] = points->m[1][bot];
  vBot[2] = points->m[2][bot];

  iTop = kdGetColor(kd, vTop);
  iMid = kdGetColor(kd, vMid);
  iBot = kdGetColor(kd, vBot);

  c0R = iBot.red;
  c0G = iBot.green;
  c0B = iBot.blue;
  c1R = iBot.red;
  c1G = iBot.green;
  c1B = iBot.blue;

  dc0R = distance0 > 0 ? ((double)iTop.red-(double)iBot.red)/(double)distance0 : 0;
  dc0G = distance0 > 0 ? ((double)iTop.green-(double)iBot.green)/(double)distance0 : 0;
  dc0B = distance0 > 0 ? ((double)iTop.blue-(double)iBot.blue)/(double)distance0 : 0;

  dc1R = distance1 > 0 ? ((double)iMid.red-(double)iBot.red)/(double)distance1 : 0;
  dc1G = distance1 > 0 ? ((double)iMid.green-(double)iBot.green)/(double)distance1 : 0;
  dc1B = distance1 > 0 ? ((double)iMid.blue-(double)iBot.blue)/(double)distance1 : 0;

  while ( y <= (int)points->m[1][top] ) {
    //printf("\tx0: %0.2f x1: %0.2f y: %d\n", x0, x1, y);

    /*v0[0] = lerp(botN[0],topN[0],(x0-xi0)/(xf-xi0));
    v0[1] = lerp(botN[1],topN[1],(y0-yi0)/(yf-yi0));
    v0[2] = lerp(botN[2],topN[2],(z0-zi0)/(zf-zi0));*/

    if ( !flip && y >= (int)(points->m[1][mid]) ) {
      flip = 1;
      dx1 = distance2 > 0 ? (points->m[0][top]-points->m[0][mid])/distance2 : 0;
      dz1 = distance2 > 0 ? (points->m[2][top]-points->m[2][mid])/distance2 : 0;

      dc1R = distance2 > 0 ? ((double)iTop.red-(double)iMid.red)/(double)distance2 : 0;
      dc1G = distance2 > 0 ? ((double)iTop.green-(double)iMid.green)/(double)distance2 : 0;
      dc1B = distance2 > 0 ? ((double)iTop.blue-(double)iMid.blue)/(double)distance2 : 0;

      c1R = iMid.red;
      c1G = iMid.green;
      c1B = iMid.blue;

      x1 = points->m[0][mid];
      z1 = points->m[2][mid];
    }//end flip code

    c0.red = (unsigned short)c0R;
    c0.green = (unsigned short)c0G;
    c0.blue = (unsigned short)c0B;

    c1.red = (unsigned short)c1R;
    c1.green = (unsigned short)c1G;
    c1.blue = (unsigned short)c1B;

    //printf("%f %f %f %f %f %f\n%d %d %d %d %d %d\n",c0R, c0G, c0B, c1R, c1G, c1B,c0.red,c0.green,c0.blue,c1.red,c1.green,c1.blue);

    draw_scanline_gouraud(x0, z0, x1, z1, y, s, zb, c0, c1);

    x0+= dx0;
    x1+= dx1;
    z0+= dz0;
    z1+= dz1;

    c0R += dc0R;
    c0G += dc0G;
    c0B += dc0B;

    c1R += dc1R;
    c1G += dc1G;
    c1B += dc1B;

    y++;

  }//end scanline loop
}

void scanline_convert_phong( struct matrix *points, struct matrix *textures,
  int i, screen s, zbuffer zb, struct kdTree* kd, 
  double* view, color ambient, struct material* mat) {

  int top, mid, bot, y;
  double vTop[3], vMid[3], vBot[3];
  double nTop[3], nMid[3], nBot[3];
  double tTop[2], tMid[2], tBot[2];
  int distance0, distance1, distance2;
  double x0, x1, y0, y1, y2, dx0, dx1, z0, z1, dz0, dz1;
  double u0, u1, v0, v1, du0, du1, dv0, dv1;
  double vec0[3], vec1[3];
  double vec0n[3], vec1n[3];
  double dVec0[3], dVec1[3];
  int flip = 0;

  z0 = z1 = dz0 = dz1 = 0;

  y0 = points->m[1][i];
  y1 = points->m[1][i+1];
  y2 = points->m[1][i+2];

  // Alas random color, we hardly knew ye
  /* color c; */
  /* c.red = (23 * (i/3))%255; */
  /* c.green = (109 * (i/3))%255; */
  /* c.blue = (c.blue+(227 * (i/3)))%255; */

  //find bot, mid, top
  if ( y0 <= y1 && y0 <= y2) {
    bot = i;
    if (y1 <= y2) {
      mid = i+1;
      top = i+2;
    }
    else {
      mid = i+2;
      top = i+1;
    }
  }//end y0 bottom
  else if (y1 <= y0 && y1 <= y2) {
    bot = i+1;
    if (y0 <= y2) {
      mid = i;
      top = i+2;
    }
    else {
      mid = i+2;
      top = i;
    }
  }//end y1 bottom
  else {
    bot = i+2;
    if (y0 <= y1) {
      mid = i;
      top = i+1;
    }
    else {
      mid = i+1;
      top = i;
    }
  }//end y2 bottom
  //printf("ybot: %0.2f, ymid: %0.2f, ytop: %0.2f\n", (points->m[1][bot]),(points->m[1][mid]), (points->m[1][top]));
  /* printf("bot: (%0.2f, %0.2f, %0.2f) mid: (%0.2f, %0.2f, %0.2f) top: (%0.2f, %0.2f, %0.2f)\n", */

  x0 = points->m[0][bot];
  x1 = points->m[0][bot];
  z0 = points->m[2][bot];
  z1 = points->m[2][bot];
  y = (int)(points->m[1][bot]);

  distance0 = (int)(points->m[1][top]) - y + 1;
  distance1 = (int)(points->m[1][mid]) - y + 1;
  distance2 = (int)(points->m[1][top]) - (int)(points->m[1][mid]) + 1;

  dx0 = distance0 > 0 ? (points->m[0][top]-points->m[0][bot])/distance0 : 0;
  dx1 = distance1 > 0 ? (points->m[0][mid]-points->m[0][bot])/distance1 : 0;
  dz0 = distance0 > 0 ? (points->m[2][top]-points->m[2][bot])/distance0 : 0;
  dz1 = distance1 > 0 ? (points->m[2][mid]-points->m[2][bot])/distance1 : 0;

  vTop[0] = points->m[0][top];
  vTop[1] = points->m[1][top];
  vTop[2] = points->m[2][top];
  tTop[0] = textures->m[0][top];
  tTop[1] = textures->m[1][top];

  vMid[0] = points->m[0][mid];
  vMid[1] = points->m[1][mid];
  vMid[2] = points->m[2][mid];
  tMid[0] = textures->m[0][mid];
  tMid[1] = textures->m[1][mid];

  vBot[0] = points->m[0][bot];
  vBot[1] = points->m[1][bot];
  vBot[2] = points->m[2][bot];
  tBot[0] = textures->m[0][bot];
  tBot[1] = textures->m[1][bot];

  set(nTop,kdGetNormal(kd, vTop));
  set(nMid,kdGetNormal(kd, vMid));
  set(nBot,kdGetNormal(kd, vBot));

  //printf("Top: %f %f %f\nMid: %f %f %f\nBot: %f %f %f\n\n", nTop[0], nTop[1], nTop[2], nMid[0], nMid[1], nMid[2], nBot[0], nBot[1], nBot[2]);
  // printf("Texture Top: u:[%lf] v:[%lf]\nTexture Mid: u:[%lf] v:[%lf]\nTexture Bot: u:[%lf] v:[%lf]\n",
  //   tTop[0], tTop[1],
  //   tMid[0], tMid[1],
  //   tBot[0], tBot[1]);
  //printf("%f\n", nBot[0] * nBot[0] + nBot[1] * nBot[1] + nBot[2] * nBot[2]);

  set(vec0, nBot);
  set(vec1, nBot);

  u0 = tBot[0];
  v0 = tBot[1];
  u1 = tBot[0];
  v1 = tBot[1];

  dVec0[0] = distance0 > 0 ? (nTop[0]-nBot[0])/distance0 : 0;
  dVec0[1] = distance0 > 0 ? (nTop[1]-nBot[1])/distance0 : 0;
  dVec0[2] = distance0 > 0 ? (nTop[2]-nBot[2])/distance0 : 0;

  dVec1[0] = distance1 > 0 ? (nMid[0]-nBot[0])/distance1 : 0;
  dVec1[1] = distance1 > 0 ? (nMid[1]-nBot[1])/distance1 : 0;
  dVec1[2] = distance1 > 0 ? (nMid[2]-nBot[2])/distance1 : 0;

  du0 = distance0 > 0 ? (tTop[0]-tBot[0])/distance0 : 0;
  dv0 = distance0 > 0 ? (tTop[1]-tBot[1])/distance0 : 0;

  du1 = distance1 > 0 ? (tMid[0]-tBot[0])/distance1 : 0;
  dv1 = distance1 > 0 ? (tMid[1]-tBot[1])/distance1 : 0;

  //printf("dVec0: %f %f %f\n", dVec0[0], dVec0[1], dVec0[2]);
  //printf("u0:[%lf] u1:[%lf] v0:[%lf] v1:[%lf] du0:[%lf] du1:[%lf] dv0:[%lf] dv1:[%lf]\n",u0,u1,v0,v1,du0,du1,dv0,dv1);

  while ( y <= (int)points->m[1][top] ) {

    if ( !flip && y >= (int)(points->m[1][mid]) ) {
      flip = 1;
      dx1 = distance2 > 0 ? (vTop[0]-vMid[0])/distance2 : 0;
      dz1 = distance2 > 0 ? (vTop[2]-vMid[1])/distance2 : 0;

      du1 = distance2 > 0 ? (tTop[0]-tMid[0])/distance2 : 0;
      dv1 = distance2 > 0 ? (tTop[1]-tMid[1])/distance2 : 0;

      dVec1[0] = distance2 > 0 ? (nTop[0]-nMid[0])/distance2 : 0;
      dVec1[1] = distance2 > 0 ? (nTop[1]-nMid[1])/distance2 : 0;
      dVec1[2] = distance2 > 0 ? (nTop[2]-nMid[2])/distance2 : 0;

      set(vec1, nMid);

      x1 = vMid[0];
      z1 = vMid[2];
      u1 = tMid[0];
      v1 = tMid[1];
    }//end flip code

    //normalize(vec0n);
    //normalize(vec1n);

    draw_scanline_phong(x0, z0, x1, z1, y, u0, u1, v0, v1, s, zb, vec0, vec1, view, ambient, mat);
    //printf("%f %f %f\n", vec0[0], vec0[1], vec0[2]);

    x0+= dx0;
    x1+= dx1;
    z0+= dz0;
    z1+= dz1;

    u0 += du0;
    u1 += du1;
    v0 += dv0;
    v1 += dv1;

    vec0[0] += dVec0[0];
    vec0[1] += dVec0[1];
    vec0[2] += dVec0[2];

    vec1[0] += dVec1[0];
    vec1[1] += dVec1[1];
    vec1[2] += dVec1[2];

    y++;

  }//end scanline loop
}

void scanline_convert_flat( struct matrix *points, struct matrix *textures,
  int i, screen s, zbuffer zb, 
  double* view, color ambient, struct material* mat, double sNormal[3]) {

  int top, mid, bot, y;
  int distance0, distance1, distance2;
  double x0, x1, y0, y1, y2, dx0, dx1, z0, z1, dz0, dz1;
  int flip = 0;

  z0 = z1 = dz0 = dz1 = 0;

  y0 = points->m[1][i];
  y1 = points->m[1][i+1];
  y2 = points->m[1][i+2];

  color c;

  c = get_lighting(sNormal,view, ambient, mat, -1, -1);

  // Alas random color, we hardly knew ye
  /* color c; */
  /* c.red = (23 * (i/3))%255; */
  /* c.green = (109 * (i/3))%255; */
  /* c.blue = (c.blue+(227 * (i/3)))%255; */

  //find bot, mid, top
  if ( y0 <= y1 && y0 <= y2) {
    bot = i;
    if (y1 <= y2) {
      mid = i+1;
      top = i+2;
    }
    else {
      mid = i+2;
      top = i+1;
    }
  }//end y0 bottom
  else if (y1 <= y0 && y1 <= y2) {
    bot = i+1;
    if (y0 <= y2) {
      mid = i;
      top = i+2;
    }
    else {
      mid = i+2;
      top = i;
    }
  }//end y1 bottom
  else {
    bot = i+2;
    if (y0 <= y1) {
      mid = i;
      top = i+1;
    }
    else {
      mid = i+1;
      top = i;
    }
  }//end y2 bottom
  //printf("ybot: %0.2f, ymid: %0.2f, ytop: %0.2f\n", (points->m[1][bot]),(points->m[1][mid]), (points->m[1][top]));
  /* printf("bot: (%0.2f, %0.2f, %0.2f) mid: (%0.2f, %0.2f, %0.2f) top: (%0.2f, %0.2f, %0.2f)\n", */

  x0 = points->m[0][bot];
  x1 = points->m[0][bot];
  z0 = points->m[2][bot];
  z1 = points->m[2][bot];
  y = (int)(points->m[1][bot]);

  distance0 = (int)(points->m[1][top]) - y + 1;
  distance1 = (int)(points->m[1][mid]) - y + 1;
  distance2 = (int)(points->m[1][top]) - (int)(points->m[1][mid]) + 1;

  dx0 = distance0 > 0 ? (points->m[0][top]-points->m[0][bot])/distance0 : 0;
  dx1 = distance1 > 0 ? (points->m[0][mid]-points->m[0][bot])/distance1 : 0;
  dz0 = distance0 > 0 ? (points->m[2][top]-points->m[2][bot])/distance0 : 0;
  dz1 = distance1 > 0 ? (points->m[2][mid]-points->m[2][bot])/distance1 : 0;

  //printf("Top: %f %f %f\nMid: %f %f %f\nBot: %f %f %f\n\n", nTop[0], nTop[1], nTop[2], nMid[0], nMid[1], nMid[2], nBot[0], nBot[1], nBot[2]);
  //printf("%f\n", nBot[0] * nBot[0] + nBot[1] * nBot[1] + nBot[2] * nBot[2]);
  //printf("dVec0: %f %f %f\n", dVec0[0], dVec0[1], dVec0[2]);

  while ( y <= (int)points->m[1][top] ) {

    if ( !flip && y >= (int)(points->m[1][mid]) ) {
      flip = 1;
      dx1 = distance2 > 0 ? (points->m[0][top]-points->m[0][mid])/distance2 : 0;
      dz1 = distance2 > 0 ? (points->m[2][top]-points->m[2][mid])/distance2 : 0;

      x1 = points->m[0][mid];
      z1 = points->m[2][mid];
    }//end flip code

    //normalize(v0n);
    //normalize(v1n);
    //printf("%f %f %f %f %f %f\n%d %d %d %d %d %d\n",c0R, c0G, c0B, c1R, c1G, c1B,c0.red,c0.green,c0.blue,c1.red,c1.green,c1.blue);

    draw_scanline_flat(x0, z0, x1, z1, y, -1, -1, -1, -1, mat, s, zb, c);
    //printf("%f %f %f\n", v0[0], v0[1], v0[2]);

    x0+= dx0;
    x1+= dx1;
    z0+= dz0;
    z1+= dz1;

    y++;

  }//end scanline loop
}

void draw_wireframe( struct matrix* points, int i, screen s, zbuffer zb, color c){
  int y0,y1,y2;
  int top, mid, bot, y;
  double vTop[3],vMid[3],vBot[3];
  struct matrix* edges = new_matrix(4,6);

  y0 = points->m[1][i];
  y1 = points->m[1][i+1];
  y2 = points->m[1][i+2];

  if ( y0 <= y1 && y0 <= y2) {
    bot = i;
    if (y1 <= y2) {
      mid = i+1;
      top = i+2;
    }
    else {
      mid = i+2;
      top = i+1;
    }
  }//end y0 bottom
  else if (y1 <= y0 && y1 <= y2) {
    bot = i+1;
    if (y0 <= y2) {
      mid = i;
      top = i+2;
    }
    else {
      mid = i+2;
      top = i;
    }
  }//end y1 bottom
  else {
    bot = i+2;
    if (y0 <= y1) {
      mid = i;
      top = i+1;
    }
    else {
      mid = i+1;
      top = i;
    }
  }//end y2 bottom

  for(int n = 0; n < 3; n++){
    vTop[n] = points->m[n][top];
    vMid[n] = points->m[n][mid];
    vBot[n] = points->m[n][bot];
  }

  add_edge(edges, vTop[0],vTop[1],vTop[2],vMid[0],vMid[1],vMid[2]);
  add_edge(edges, vMid[0],vMid[1],vMid[2],vBot[0],vBot[1],vBot[2]);
  add_edge(edges, vBot[0],vBot[1],vBot[2],vTop[0],vTop[1],vTop[2]);

  draw_lines(edges, s, zb, c);

  free_matrix(edges);

}

/*======== void add_polygon() ==========
  Inputs:   struct matrix *polygons
            double x0
            double y0
            double z0
            double x1
            double y1
            double z1
            double x2
            double y2
            double z2
  Returns:
  Adds the vertices (x0, y0, z0), (x1, y1, z1)
  and (x2, y2, z2) to the polygon matrix. They
  define a single triangle surface.
  ====================*/
void add_polygon( struct matrix *polygons,
                  double x0, double y0, double z0,
                  double x1, double y1, double z1,
                  double x2, double y2, double z2 ) {
  add_point(polygons, x0, y0, z0);
  add_point(polygons, x1, y1, z1);
  add_point(polygons, x2, y2, z2);
}

struct kdTree* compute_vertex_normals(struct matrix* polygons){

  int point;
  double *normal;
  double v0[3];
  double v1[3];
  double v2[3];
  //struct hashTable* h = createHT(65536);
  struct kdTree* kd = kdCreate();
  double** normals = malloc(sizeof(double) * (polygons->lastcol));

  double drawPercent = 0;
  double percentChange = 1.0 / (double)(polygons->lastcol/3);

  for (point=0; point < polygons->lastcol-2; point+=3) {

    drawPercent += percentChange;
    //printf("\e[1;1H\e[2J");

    normal = calculate_normal(polygons, point);
    normalize(normal);
    //normals[point/3] = normal;

    v0[0] = polygons->m[0][point];
    v0[1] = polygons->m[1][point];
    v0[2] = polygons->m[2][point];

    v1[0] = polygons->m[0][point+1];
    v1[1] = polygons->m[1][point+1];
    v1[2] = polygons->m[2][point+1];

    v2[0] = polygons->m[0][point+2];
    v2[1] = polygons->m[1][point+2];
    v2[2] = polygons->m[2][point+2];

    kd = kdInsert(kd, v0, normal);
    kd = kdInsert(kd, v1, normal);
    kd = kdInsert(kd, v2, normal);

    //printf("Generating lighting\t%d percent complete\n", (int)(drawPercent*100));
  }

  return kd;

}

/*======== void draw_polygons() ==========
  Inputs:   struct matrix *polygons
            screen s
            color c
  Returns:
  Goes through polygons 3 points at a time, drawing
  lines connecting each points to create bounding triangles
  ====================*/
void draw_polygons( struct matrix *polygons, struct matrix* textures,
  struct kdTree* kd, screen s, zbuffer zb,
  double *view, color ambient,
  int shaderType) {
  
  if ( polygons->lastcol < 3 ) {
    printf("Need at least 3 points to draw a polygon!\n");
    return;
  }

  int point;
  int forceNormalCreation = 0;

  //print_materials();

  double drawPercent = 0;
  double percentChange = 1.0 / (double)(polygons->lastcol/3);
  struct constants finalConstants;
  int currentMaterialID, prevMaterialID;

  double* normal;

  color wireframeColor;
  struct material* currentMaterial;

  wireframeColor.red = 255;
  wireframeColor.green = 255;
  wireframeColor.blue = 255;

  if(forceNormalCreation || kd == NULL || kd->changed == 0){
    //printf("No vertex normal table! Creating one...\n");
    //if(kd != NULL) kdFree(kd);
    kd = compute_vertex_normals(polygons);
    kdNormalize(kd,view, ambient,0);
  }
  //kdCheck(kd, polygons);

  //kdPrint(kd);

  prevMaterialID = -1;

  drawPercent = 0;
  for(point = 0; point < polygons->lastcol-2; point+=3){
    //normal = calculate_normal(polygons, point);
    //printf("%f %f %f\n",normal[0],normal[1],normal[2]);

    //printf("\e[1;1H\e[2J");

    drawPercent += percentChange;


    normal = calculate_normal(polygons,point);
    normalize(normal);
    if ( normal[2] > 0 ) {

      //printf("%lf %lf %lf\n",polygons->m[0][point],polygons->m[1][point],polygons->m[2][point]);

      // get color value only if front facing
      //color i = get_lighting(normal, view, ambient, light, areflect, dreflect, sreflect);

      //print_matrix(materials);
      //printf("%d\n", (int)textures->m[2][point]);
      //printf("%s\n", find_material_name((int)textures->m[2][point]));
      currentMaterial = find_material(find_material_name((int)textures->m[2][point]));
      currentMaterialID = currentMaterial->id;

      // finalConstants.r[AMBIENT_R] = currentMaterial->ka[0];
      // finalConstants.g[AMBIENT_R] = currentMaterial->ka[1];
      // finalConstants.b[AMBIENT_R] = currentMaterial->ka[2];

      // finalConstants.r[DIFFUSE_R] = currentMaterial->kd[0];
      // finalConstants.g[DIFFUSE_R] = currentMaterial->kd[1];
      // finalConstants.b[DIFFUSE_R] = currentMaterial->kd[2];

      // finalConstants.r[SPECULAR_R] = currentMaterial->ks[0];
      // finalConstants.g[SPECULAR_R] = currentMaterial->ks[1];
      // finalConstants.b[SPECULAR_R] = currentMaterial->ks[2];

      //finalSpecExp = currentMaterial->ns;

      if(prevMaterialID != currentMaterialID){
        kd = kdNormalize(kd, view, ambient, currentMaterialID);
        prevMaterialID = currentMaterialID;
      }

      if(shaderType == SHADER_GOURAUD) scanline_convert_gouraud(polygons, textures, point, s, zb, kd, currentMaterial);
      else if(shaderType == SHADER_PHONG) scanline_convert_phong(polygons, textures, point, s, zb, kd, view, ambient, currentMaterial);
      else if(shaderType == SHADER_FLAT) scanline_convert_flat(polygons, textures, point, s, zb, view, ambient, currentMaterial, normal);
      else if(shaderType == SHADER_WIREFRAME) draw_wireframe(polygons, point,s,zb,wireframeColor);

      /* draw_line( polygons->m[0][point], */
      /*            polygons->m[1][point], */
      /*            polygons->m[2][point], */
      /*            polygons->m[0][point+1], */
      /*            polygons->m[1][point+1], */
      /*            polygons->m[2][point+1], */
      /*            s, zb, c); */
      /* draw_line( polygons->m[0][point+2], */
      /*            polygons->m[1][point+2], */
      /*            polygons->m[2][point+2], */
      /*            polygons->m[0][point+1], */
      /*            polygons->m[1][point+1], */
      /*            polygons->m[2][point+1], */
      /*            s, zb, c); */
      /* draw_line( polygons->m[0][point], */
      /*            polygons->m[1][point], */
      /*            polygons->m[2][point], */
      /*            polygons->m[0][point+2], */
      /*            polygons->m[1][point+2], */
      /*            polygons->m[2][point+2], */
      /*            s, zb, c); */
    }
    //printf("Drawing\t%d percent complete\n", (int)(drawPercent*100));
  }

  //freeHT(h);
  //kdFree(kd);
}
/*======== void add_box() ==========
  Inputs:   struct matrix * edges
            double x
            double y
            double z
            double width
            double height
            double depth

  add the points for a rectagular prism whose
  upper-left-front corner is (x, y, z) with width,
  height and depth dimensions.
  ====================*/
void add_box( struct matrix *polygons, struct matrix *textures,
  double matID,
  double x, double y, double z,
  double width, double height, double depth ) {
  // double x0, y0, z0, x1, y1, z1;
  // x0 = x;
  // x1 = x+width;
  // y0 = y;
  // y1 = y-height;
  // z0 = z;
  // z1 = z-depth;


  // //front
  // add_polygon(polygons, x, y, z, x1, y1, z, x1, y, z);
  // add_polygon(polygons, x, y, z, x, y1, z, x1, y1, z);
  // //back
  // add_polygon(polygons, x1, y, z1, x, y1, z1, x, y, z1);
  // add_polygon(polygons, x1, y, z1, x1, y1, z1, x, y1, z1);

  // //right side
  // add_polygon(polygons, x1, y, z, x1, y1, z1, x1, y, z1);
  // add_polygon(polygons, x1, y, z, x1, y1, z, x1, y1, z1);
  // //left side
  // add_polygon(polygons, x, y, z1, x, y1, z, x, y, z);
  // add_polygon(polygons, x, y, z1, x, y1, z1, x, y1, z);

  // //top
  // add_polygon(polygons, x, y, z1, x1, y, z, x1, y, z1);
  // add_polygon(polygons, x, y, z1, x, y, z, x1, y, z);
  // //bottom
  // add_polygon(polygons, x, y1, z, x1, y1, z1, x1, y1, z);
  // add_polygon(polygons, x, y1, z, x, y1, z1, x1, y1, z1);

  double p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z,p4x,p4y,p4z,p5x,p5y,p5z,p6x,p6y,p6z,p7x,p7y,p7z,p8x,p8y,p8z;

  p1x = x;
  p1y = y;
  p1z = z;

  p2x = x+width;
  p2y = y;
  p2z = z;

  p3x = x;
  p3y = y-height;
  p3z = z;

  p4x = x+width;
  p4y = y-height;
  p4z = z;

  p5x = x;
  p5y = y;
  p5z = z-depth;

  p6x = x+width;
  p6y = y;
  p6z = z-depth;

  p7x = x;
  p7y = y-height;
  p7z = z-depth;

  p8x = x+width;
  p8y = y-height;
  p8z = z-depth;

  add_polygon(polygons,p1x,p1y,p1z,p3x,p3y,p3z,p2x,p2y,p2z);
  add_polygon(polygons,p3x,p3y,p3z,p4x,p4y,p4z,p2x,p2y,p2z);

  add_polygon(polygons,p6x,p6y,p6z,p8x,p8y,p8z,p5x,p5y,p5z);
  add_polygon(polygons,p8x,p8y,p8z,p7x,p7y,p7z,p5x,p5y,p5z);

  add_polygon(polygons,p1x,p1y,p1z,p2x,p2y,p2z,p5x,p5y,p5z);
  add_polygon(polygons,p2x,p2y,p2z,p6x,p6y,p6z,p5x,p5y,p5z);

  add_polygon(polygons,p7x,p7y,p7z,p8x,p8y,p8z,p3x,p3y,p3z);
  add_polygon(polygons,p8x,p8y,p8z,p4x,p4y,p4z,p3x,p3y,p3z);

  add_polygon(polygons,p7x,p7y,p7z,p3x,p3y,p3z,p5x,p5y,p5z);
  add_polygon(polygons,p3x,p3y,p3z,p1x,p1y,p1z,p5x,p5y,p5z);

  add_polygon(polygons,p4x,p4y,p4z,p8x,p8y,p8z,p2x,p2y,p2z);
  add_polygon(polygons,p8x,p8y,p8z,p6x,p6y,p6z,p2x,p2y,p2z);



  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);

  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);

  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);

  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);

  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);

  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
  add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);

}

void add_plane(struct matrix* polygons,
  double x, double y, double z,
  double width, double height){

  double x0, y0, x1, y1;
  x0 = x;
  y0 = y;
  x1 = x + width;
  y1 = y + height;

  add_polygon(polygons, x0, y1, z, x0, y0, z, x1, y1, z);
  add_polygon(polygons, x0, y0, z, x1, y0, z, x1, y1, z);

  //add_polygon(polygons, x0, y0, z, x0, y1, z, x1, y1, z);
  //add_polygon(polygons, x1, y0, z, x0, y0, z, x1, y1, z);

}


/*======== void add_sphere() ==========
  Inputs:   struct matrix * points
            double cx
            double cy
            double cz
            double r
            int step

  adds all the points for a sphere with center (cx, cy, cz)
  and radius r using step points per circle/semicircle.

  Since edges are drawn using 2 points, add each point twice,
  or add each point and then another point 1 pixel away.

  should call generate_sphere to create the necessary points
  ====================*/
void add_sphere( struct matrix * edges, struct matrix* textures, 
  double matID,
  double cx, double cy, double cz,
  double r, int step ) {

  struct matrix *points = generate_sphere(cx, cy, cz, r, step);
  int p0, p1, p2, p3, lat, longt;
  int latStop, longStop, latStart, longStart;
  latStart = 0;
  latStop = step;
  longStart = 1;
  longStop = step;

  //step++; needed for my triangles
  for ( lat = latStart; lat < latStop; lat++ ) {
    for ( longt = longStart; longt < longStop; longt++ ) {

      /*Milan's Triangles*/
      p0 = lat * (step+1) + longt;
      p1 = p0 + 1;
      p2 = (p1 + step) % (step * (step+1));
      p3 = (p0 + step) % (step * (step+1));

      add_polygon( edges, points->m[0][p0],
                   points->m[1][p0],
                   points->m[2][p0],
                   points->m[0][p1],
                   points->m[1][p1],
                   points->m[2][p1],
                   points->m[0][p2],
                   points->m[1][p2],
                   points->m[2][p2]);
      add_polygon( edges, points->m[0][p0],
                   points->m[1][p0],
                   points->m[2][p0],
                   points->m[0][p2],
                   points->m[1][p2],
                   points->m[2][p2],
                   points->m[0][p3],
                   points->m[1][p3],
                   points->m[2][p3]);

      add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
      add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);

      /*My Triangles*/
      /* p0 = lat * (step) + longt; */
      /* p1 = p0+1; */
      /* p2 = (p1+step) % (step * (step-1)); */
      /* p3 = (p0+step) % (step * (step-1)); */

      /* //printf("p0: %d\tp1: %d\tp2: %d\tp3: %d\n", p0, p1, p2, p3); */
      /* if (longt < step - 2) */
      /*   add_polygon( edges, points->m[0][p0], */
      /*                points->m[1][p0], */
      /*                points->m[2][p0], */
      /*                points->m[0][p1], */
      /*                points->m[1][p1], */
      /*                points->m[2][p1], */
      /*                points->m[0][p2], */
      /*                points->m[1][p2], */
      /*                points->m[2][p2]); */
      /* if (longt > 0 ) */
      /*   add_polygon( edges, points->m[0][p0], */
      /*                points->m[1][p0], */
      /*                points->m[2][p0], */
      /*                points->m[0][p2], */
      /*                points->m[1][p2], */
      /*                points->m[2][p2], */
      /*                points->m[0][p3], */
      /*                points->m[1][p3], */
      /*                points->m[2][p3]); */
    }
  }
  free_matrix(points);
}

/*======== void generate_sphere() ==========
  Inputs:   struct matrix * points
            double cx
            double cy
            double cz
            double r
            int step
  Returns: Generates all the points along the surface
           of a sphere with center (cx, cy, cz) and
           radius r using step points per circle/semicircle.
           Returns a matrix of those points
  ====================*/
struct matrix * generate_sphere(double cx, double cy, double cz,
  double r, int step ) {

  struct matrix *points = new_matrix(4, step * step);
  int circle, rotation, rot_start, rot_stop, circ_start, circ_stop;
  double x, y, z, rot, circ;

  rot_start = 0;
  rot_stop = step;
  circ_start = 0;
  circ_stop = step;

  for (rotation = rot_start; rotation < rot_stop; rotation++) {
    rot = (double)rotation / step;

    for(circle = circ_start; circle <= circ_stop; circle++){
      circ = (double)circle / step;

      x = r * cos(M_PI * circ) + cx;
      y = r * sin(M_PI * circ) *
        cos(2*M_PI * rot) + cy;
      z = r * sin(M_PI * circ) *
        sin(2*M_PI * rot) + cz;

      /* printf("rotation: %d\tcircle: %d\n", rotation, circle); */
      /* printf("rot: %lf\tcirc: %lf\n", rot, circ); */
      /* printf("sphere point: (%0.2f, %0.2f, %0.2f)\n\n", x, y, z); */
      add_point(points, x, y, z);
    }
  }

  return points;
}

/*======== void add_torus() ==========
  Inputs:   struct matrix * points
            double cx
            double cy
            double cz
            double r1
            double r2
            double step
  Returns:

  adds all the points required for a torus with center (cx, cy, cz),
  circle radius r1 and torus radius r2 using step points per circle.

  should call generate_torus to create the necessary points
  ====================*/
void add_torus( struct matrix * edges, struct matrix *textures,
  double matID,
  double cx, double cy, double cz,
  double r1, double r2, int step ) {

  struct matrix *points = generate_torus(cx, cy, cz, r1, r2, step);
  int p0, p1, p2, p3, lat, longt;
  int latStop, longStop, latStart, longStart;
  latStart = 0;
  latStop = step;
  longStart = 0;
  longStop = step;

  for ( lat = latStart; lat < latStop; lat++ ) {
    for ( longt = longStart; longt < longStop; longt++ ) {
      p0 = lat * step + longt;
      if (longt == step - 1)
        p1 = p0 - longt;
      else
        p1 = p0 + 1;
      p2 = (p1 + step) % (step * step);
      p3 = (p0 + step) % (step * step);

      //printf("p0: %d\tp1: %d\tp2: %d\tp3: %d\n", p0, p1, p2, p3);
      add_polygon( edges, points->m[0][p0],
                   points->m[1][p0],
                   points->m[2][p0],
                   points->m[0][p3],
                   points->m[1][p3],
                   points->m[2][p3],
                   points->m[0][p2],
                   points->m[1][p2],
                   points->m[2][p2]);
      add_polygon( edges, points->m[0][p0],
                   points->m[1][p0],
                   points->m[2][p0],
                   points->m[0][p2],
                   points->m[1][p2],
                   points->m[2][p2],
                   points->m[0][p1],
                   points->m[1][p1],
                   points->m[2][p1]);

      add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
      add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
    }
  }
  free_matrix(points);
}

/*======== void generate_torus() ==========
  Inputs:   struct matrix * points
            double cx
            double cy
            double cz
            double r
            int step
  Returns: Generates all the points along the surface
           of a torus with center (cx, cy, cz),
           circle radius r1 and torus radius r2 using
           step points per circle.
           Returns a matrix of those points
  ====================*/
struct matrix * generate_torus( double cx, double cy, double cz,
  double r1, double r2, int step ) {

  struct matrix *points = new_matrix(4, step * step);
  int circle, rotation, rot_start, rot_stop, circ_start, circ_stop;
  double x, y, z, rot, circ;

  rot_start = 0;
  rot_stop = step;
  circ_start = 0;
  circ_stop = step;

  for (rotation = rot_start; rotation < rot_stop; rotation++) {
    rot = (double)rotation / step;

    for(circle = circ_start; circle < circ_stop; circle++){
      circ = (double)circle / step;

      x = cos(2*M_PI * rot) *
        (r1 * cos(2*M_PI * circ) + r2) + cx;
      y = r1 * sin(2*M_PI * circ) + cy;
      z = -1*sin(2*M_PI * rot) *
        (r1 * cos(2*M_PI * circ) + r2) + cz;

      //printf("rotation: %d\tcircle: %d\n", rotation, circle);
      //printf("torus point: (%0.2f, %0.2f, %0.2f)\n", x, y, z);
      add_point(points, x, y, z);
    }
  }
  return points;
}

void add_cylinder( struct matrix* edges, struct matrix* textures,
  double matID,
  double cx, double cy, double cz,
  double r, double h, int step){

  struct matrix* points = generate_cylinder(cx,cy,cz,r,h,step);

  int longt, longtStart, longtStop;
  int p0, p1, p2, p3;

  double pTop[3], pBot[3];

  pTop[0] = cx;
  pTop[1] = cy + (h / 2.0);
  pTop[2] = cz;

  pBot[0] = cx;
  pBot[1] = cy - (h / 2.0);
  pBot[2] = cz;

  longtStart = 0;
  longtStop = step;

  for(int longt = longtStart; longt < longtStop; longt++){
    p0 = step + (longt % step);
    p1 = step + ((longt + 1) % step);
    p2 = (longt + 1) % step;
    p3 = longt % step;

    //printf("%lf %lf %lf\n", points->m[0][p0], points->m[1][p0],points->m[2][p0]);

    add_polygon(edges, points->m[0][p0], points->m[1][p0],points->m[2][p0],
      points->m[0][p1], points->m[1][p1],points->m[2][p1],
      points->m[0][p2], points->m[1][p2],points->m[2][p2]);
    add_polygon(edges, points->m[0][p0], points->m[1][p0],points->m[2][p0],
      points->m[0][p2], points->m[1][p2],points->m[2][p2],
      points->m[0][p3], points->m[1][p3],points->m[2][p3]);

    add_polygon(edges,pTop[0],pTop[1],pTop[2],
      points->m[0][p3], points->m[1][p3],points->m[2][p3],
      points->m[0][p2], points->m[1][p2],points->m[2][p2]);

    add_polygon(edges,pBot[0],pBot[1],pBot[2],
      points->m[0][p1], points->m[1][p1],points->m[2][p1],
      points->m[0][p0], points->m[1][p0],points->m[2][p0]);

    add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
    add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
    add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
    add_polygon(textures, -1, -1, matID, -1, -1, matID, -1, -1, matID);
  }

  free_matrix(points);

}

struct matrix* generate_cylinder( double cx, double cy, double cz,
  double r, double h, int step){

  struct matrix* points = new_matrix(4, step*2);
  int rotation, rot_start, rot_stop;
  double x, y, z, rot;

  rot_start = 0;
  rot_stop = step;

  for(rotation = rot_start; rotation < rot_stop; rotation++){

    rot = (double)rotation / step;

    x = r * cos(2 * M_PI * rot) + cx;
    y = cy + (h / 2.0);
    z = r * sin(-2 * M_PI * rot) + cz;

    //printf("%lf %lf %lf\n",x,y,z);

    add_point(points,x,y,z);

  }

  for(rotation = rot_start; rotation < rot_stop; rotation++){

    rot = (double)rotation / step;

    x = r * cos(2 * M_PI * rot) + cx;
    y = cy - (h / 2.0);
    z = r * sin(-2 * M_PI * rot) + cz;

    add_point(points,x,y,z);

  }

  return points;

}

/*======== void add_circle() ==========
  Inputs:   struct matrix * edges
            double cx
            double cy
            double r
            double step

  Adds the circle at (cx, cy) with radius r to edges
  ====================*/
void add_circle( struct matrix *edges,
                 double cx, double cy, double cz,
                 double r, int step ) {
  double x0, y0, x1, y1, t;
  int i;

  x0 = r + cx;
  y0 = cy;
  for (i=1; i<=step; i++) {
    t = (double)i/step;
    x1 = r * cos(2 * M_PI * t) + cx;
    y1 = r * sin(2 * M_PI * t) + cy;

    add_edge(edges, x0, y0, cz, x1, y1, cz);
    x0 = x1;
    y0 = y1;
  }
}


/*======== void add_curve() ==========
Inputs:   struct matrix *edges
         double x0
         double y0
         double x1
         double y1
         double x2
         double y2
         double x3
         double y3
         double step
         int type

Adds the curve bounded by the 4 points passsed as parameters
of type specified in type (see matrix.h for curve type constants)
to the matrix edges
====================*/
void add_curve( struct matrix *edges,
                double x0, double y0, 
                double x1, double y1, 
                double x2, double y2, 
                double x3, double y3, 
                int step, int type ) {
  double t, x, y;
  int i;
  struct matrix *xcoefs;
  struct matrix *ycoefs;

  xcoefs = generate_curve_coefs(x0, x1, x2, x3, type);
  ycoefs = generate_curve_coefs(y0, y1, y2, y3, type);
  
  /* print_matrix(xcoefs); */
  /* printf("\n"); */
  /* print_matrix(ycoefs); */
  
  for (i=1; i<=step; i++) {
    t = (double)i/step;

    x = xcoefs->m[0][0] *t*t*t + xcoefs->m[1][0] *t*t+
      xcoefs->m[2][0] *t + xcoefs->m[3][0];
    y = ycoefs->m[0][0] *t*t*t + ycoefs->m[1][0] *t*t+
      ycoefs->m[2][0] *t + ycoefs->m[3][0];

    add_edge(edges, x0, y0, 0, x, y, 0);
    x0 = x;
    y0 = y;
  }

  free_matrix(xcoefs);
  free_matrix(ycoefs);
}



/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {

  if ( points->lastcol == points->cols ){
    grow_matrix( points, points->cols*2 );
  }
  
  points->m[0][ points->lastcol ] = x;
  points->m[1][ points->lastcol ] = y;
  points->m[2][ points->lastcol ] = z;
  points->m[3][ points->lastcol ] = 1;
  points->lastcol++;
} //end add_point

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point( points, x0, y0, z0 );
  add_point( points, x1, y1, z1 );
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, zbuffer zb, color c) {

 if ( points->lastcol < 2 ) {
   printf("Need at least 2 points to draw a line!\n");
   return;
 }

 int point;
 for (point=0; point < points->lastcol-1; point+=2)
   draw_line( points->m[0][point],
              points->m[1][point],
              points->m[2][point],
              points->m[0][point+1],
              points->m[1][point+1],
              points->m[2][point+1],
              s, zb, c);
}// end draw_lines


void draw_line(int x0, int y0, double z0,
               int x1, int y1, double z1,
               screen s, zbuffer zb, color c) {

  int x, y, d, A, B;
  int dy_east, dy_northeast, dx_east, dx_northeast, d_east, d_northeast;
  int loop_start, loop_end;
  double distance;
  double z, dz;

  //swap points if going right -> left
  int xt, yt;
  if (x0 > x1) {
    xt = x0;
    yt = y0;
    x0 = x1;
    y0 = y1;
    z0 = z1;
    x1 = xt;
    y1 = yt;
  }

  x = x0;
  y = y0;
  A = 2 * (y1 - y0);
  B = -2 * (x1 - x0);
  int wide = 0;
  int tall = 0;
  //octants 1 and 8
  if ( abs(x1 - x0) >= abs(y1 - y0) ) { //octant 1/8
    wide = 1;
    loop_start = x;
    loop_end = x1;
    dx_east = dx_northeast = 1;
    dy_east = 0;
    d_east = A;
    distance = x1 - x + 1;
    if ( A > 0 ) { //octant 1
      d = A + B/2;
      dy_northeast = 1;
      d_northeast = A + B;
    }
    else { //octant 8
      d = A - B/2;
      dy_northeast = -1;
      d_northeast = A - B;
    }
  }//end octant 1/8
  else { //octant 2/7
    tall = 1;
    dx_east = 0;
    dx_northeast = 1;
    distance = abs(y1 - y) + 1;
    if ( A > 0 ) {     //octant 2
      d = A/2 + B;
      dy_east = dy_northeast = 1;
      d_northeast = A + B;
      d_east = B;
      loop_start = y;
      loop_end = y1;
    }
    else {     //octant 7
      d = A/2 - B;
      dy_east = dy_northeast = -1;
      d_northeast = A - B;
      d_east = -1 * B;
      loop_start = y1;
      loop_end = y;
    }
  }

  z = z0;
  dz = (z1 - z0) / distance;
  while ( loop_start < loop_end ) {

    plot( s, zb, c, x, y, z);
    if ( (wide && ((A > 0 && d > 0) ||
                   (A < 0 && d < 0)))
         ||
         (tall && ((A > 0 && d < 0 ) ||
                   (A < 0 && d > 0) ))) {
      y+= dy_northeast;
      d+= d_northeast;
      x+= dx_northeast;
    }
    else {
      x+= dx_east;
      y+= dy_east;
      d+= d_east;
    }
    z+= dz;
    loop_start++;
  } //end drawing loop
  plot( s, zb, c, x1, y1, z );
} //end draw_line
