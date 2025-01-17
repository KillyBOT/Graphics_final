/*========== my_main.c ==========

  This is the only file you need to modify in order
  to get a working mdl project (for now).

  my_main.c will serve as the interpreter for mdl.
  When an mdl script goes through a lexer and parser,
  the resulting operations will be in the array op[].

  Your job is to go through each entry in op and perform
  the required action from the list below:

  push: push a new origin matrix onto the origin stack

  pop: remove the top matrix on the origin stack

  move/scale/rotate: create a transformation matrix
                     based on the provided values, then
                     multiply the current top of the
                     origins stack by it.

  box/sphere/torus: create a solid object based on the
                    provided values. Store that in a
                    temporary matrix, multiply it by the
                    current top of the origins stack, then
                    call draw_polygons.

  line: create a line based on the provided values. Store
        that in a temporary matrix, multiply it by the
        current top of the origins stack, then call draw_lines.

  save: call save_extension with the provided filename

  display: view the screen
  =========================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ml6.h"
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"
#include "matrix.h"
#include "display.h"
#include "draw.h"
#include "stack.h"
#include "gmath.h"
#include "kdTree.h"
#include "convert.h"
#include "material.h"

extern struct material* m;
extern struct material_id* mI;

extern regex_t qF;
extern regex_t qFT;
extern regex_t qFN;
extern regex_t qFTN;

extern regex_t tF;
extern regex_t tFT;
extern regex_t tFN;
extern regex_t tFTN;

/*======== void first_pass() ==========
  Inputs:
  Returns:

  Checks the op array for any animation commands
  (frames, basename, vary)

  Should set num_frames and basename if the frames
  or basename commands are present

  If vary is found, but frames is not, the entire
  program should exit.

  If frames is found, but basename is not, set name
  to some default value, and print out a message
  with the name being used.

  This pass will also load meshes, textures, and constants
  ====================*/
void first_pass() {
  //These variables are defined at the bottom of symtab.h
  extern int num_frames;
  extern char name[128];

  int varyFound, framesFound, basenameFound;
  varyFound = 0;
  framesFound = 0;
  basenameFound = 0;
  struct matrix* polys;
  struct matrix* textures;
  struct kdTree* meshKD;
  int matID;
  char finalName[512];

  num_frames = 1;
  matID = 0;

  struct vary_node* knobs = NULL;
  struct vary_node* curr;
  struct vary_node* prev = NULL;
  struct light* tmpLight;
  struct kdTree* kd;

  struct material* tmpMat;
  struct constants white;
  int specExp;

  white.r[AMBIENT_R] = 0.1;
  white.g[AMBIENT_R] = 0.1;
  white.b[AMBIENT_R] = 0.1;

  white.r[DIFFUSE_R] = 0.5;
  white.g[DIFFUSE_R] = 0.5;
  white.b[DIFFUSE_R] = 0.5;

  white.r[SPECULAR_R] = 0.5;
  white.g[SPECULAR_R] = 0.5;
  white.b[SPECULAR_R] = 0.5;

  specExp = 128;

  add_material("DefaultMaterial");
  tmpMat = find_material("DefaultMaterial");

  tmpMat->ka[0] = white.r[AMBIENT_R];
  tmpMat->ka[1] = white.g[AMBIENT_R];
  tmpMat->ka[2] = white.b[AMBIENT_R];

  tmpMat->kd[0] = white.r[DIFFUSE_R];
  tmpMat->kd[1] = white.g[DIFFUSE_R];
  tmpMat->kd[2] = white.b[DIFFUSE_R];

  tmpMat->ks[0] = white.r[SPECULAR_R];
  tmpMat->ks[1] = white.g[SPECULAR_R];
  tmpMat->ks[2] = white.b[SPECULAR_R];

  tmpMat->ns = specExp;

  char* knobName;
  double knobVal;

  for(int i=0;i<lastop;i++){
    //printf("%d: ", i);
    switch(op[i].opcode){
      case CONSTANTS:

          add_material(op[i].op.constants.p->name);

          tmpMat = find_material(op[i].op.constants.p->name);

          tmpMat->ka[0] = op[i].op.constants.p->s.c->r[0];
          tmpMat->ka[1] = op[i].op.constants.p->s.c->g[0];
          tmpMat->ka[2] = op[i].op.constants.p->s.c->b[0];

          tmpMat->kd[0] = op[i].op.constants.p->s.c->r[1];
          tmpMat->kd[1] = op[i].op.constants.p->s.c->g[1];
          tmpMat->kd[2] = op[i].op.constants.p->s.c->b[1];

          tmpMat->ks[0] = op[i].op.constants.p->s.c->r[2];
          tmpMat->ks[1] = op[i].op.constants.p->s.c->g[2];
          tmpMat->ks[2] = op[i].op.constants.p->s.c->b[2];

          tmpMat->ns = 32;

          break;
      case FRAMES:

        num_frames = (int)op[i].op.frames.num_frames;

        framesFound = 1;

        break;

      case BASENAME:

        strcpy(name, op[i].op.basename.p->name);

        basenameFound = 1;

        break;

      case MESH:

        if(op[i].op.mesh.constants != NULL){
          matID = find_material(op[i].op.mesh.constants->name)->id;
        }
        //printf("%s %d\n", op[i].op.mesh.constants->name, matID);

        add_symbol(op[i].op.mesh.name, SYM_FILE, 0);

        polys = new_matrix(4, 1024);
        textures = new_matrix(4, 1024);

        meshKD = convert(polys,textures,(double)matID,op[i].op.mesh.name);

        //sscanf(finalName,"%s%s",op[i].op.mesh.name,"_polygons");
        strcpy(finalName,op[i].op.mesh.name);
        strcat(finalName,"_polygons_");
        if(op[i].op.mesh.constants != NULL)strcat(finalName,op[i].op.mesh.constants->name);
        add_symbol(finalName,SYM_MATRIX,polys);

        //sscanf(finalName,"%s%s",op[i].op.mesh.name,"_textures");
        strcpy(finalName,op[i].op.mesh.name);
        strcat(finalName,"_textures_");
        if(op[i].op.mesh.constants != NULL)strcat(finalName,op[i].op.mesh.constants->name);
        add_symbol(finalName,SYM_MATRIX,textures);

        //sscanf(finalName,"%s%s",op[i].op.mesh.name,"_kdtree");
        strcpy(finalName,op[i].op.mesh.name);
        strcat(finalName,"_kdTree_");
        if(op[i].op.mesh.constants != NULL)strcat(finalName,op[i].op.mesh.constants->name);
        add_symbol(finalName,SYM_KDTREE,meshKD);

        //print_symtab();

        matID = 0;

        break;

      case SET:

        if(lookup_symbol(op[i].op.set.p->name) == NULL){
          //printf("Adding %s\n", op[i].op.set.p->name);
          add_symbol(op[i].op.set.p->name,SYM_VALUE,0);
        }

        set_value(lookup_symbol(op[i].op.set.p->name),op[i].op.set.val);

        break;

      case LIGHT:

        tmpLight = lookup_symbol(op[i].op.light.p->name)->s.l;

          for(int n = 0; n < 3; n++){
            tmpLight->l[n] = op[i].op.light.l[n];
            tmpLight->c[n] = op[i].op.light.c[n];
          }

        break;

      case VARY:

        varyFound = 1;

        break;

      case TWEEN:

        varyFound = 1;

        break;

      case SAVE_KNOBS:

        knobs = malloc(sizeof(struct vary_node));
        knobs->next = NULL;
        curr = knobs;

        for(int n = 0; n < lastsym; n++){
          if(symtab[n].type == SYM_VALUE){

            if(curr == NULL) curr = malloc(sizeof(struct vary_node));

            strcpy(curr->name,symtab[n].name);
            curr->value = symtab[n].s.value;
            curr->next = NULL;

            if(prev != NULL) prev->next = curr;

            prev = curr;
            curr = curr->next;

          }
        }
        prev = NULL;

        //if(lookup_symbol(op[i].op.save_knobs.p->name) == NULL) add_symbol(op[i].op.save_knobs.p->name,SYM_KNOBLIST,knobs);
        lookup_symbol(op[i].op.save_knobs.p->name)->s.v = knobs;
        //printf("%s\n", op[i].op.save_knobs.p->name);
        //printf("%lf\n",lookup_symbol(op[i].op.save_knobs.p->name)->s.v->value);
        //if(lookup_symbol(op[i].op.save_knobs.p->name)->s.v->next != NULL) printf("Somethings wrong...\n");
        //curr = NULL;
        //knobs = NULL;

        //print_symtab();

        break;
    }
  }

  if(varyFound && !framesFound){
    printf("Frames not found! Exiting...\n");
    exit(1);
  }

  if(framesFound && !basenameFound){

    strcpy(name,"fyjshk");

    printf("Basename not found! Defaulting to %s\n", name);
  }

}

/*======== struct vary_node ** second_pass() ==========
  Inputs:
  Returns: An array of vary_node linked lists

  In order to set the knobs for animation, we need to keep
  a seaprate value for each knob for each frame. We can do
  this by using an array of linked lists. Each array index
  will correspond to a frame (eg. knobs[0] would be the first
  frame, knobs[2] would be the 3rd frame and so on).

  Each index should contain a linked list of vary_nodes, each
  node contains a knob name, a value, and a pointer to the
  next node.

  Go through the opcode array, and when you find vary, go
  from knobs[0] to knobs[frames-1] and add (or modify) the
  vary_node corresponding to the given knob with the
  appropirate value.
  ====================*/
struct vary_node ** second_pass() {

  extern int num_frames;
  extern char name[128];

  struct vary_node *curr = NULL;
  struct vary_node* curr_tween = NULL;
  struct vary_node* curr_tween_knob = NULL;
  struct vary_node* startKnob;
  struct vary_node* endKnob;
  struct vary_node **knobs;
  knobs = (struct vary_node **)calloc(num_frames, sizeof(struct vary_node *));

  double valChange;
  double currentVal;
  double startVal;
  double endVal;
  int changed;

  for(int i = 0; i < lastop; i++){
    switch(op[i].opcode){
      case VARY:

        startVal = op[i].op.vary.start_val;
        endVal = op[i].op.vary.end_val;

        valChange = (endVal - startVal)/(op[i].op.vary.end_frame - op[i].op.vary.start_frame);
        currentVal = startVal;

        if(lookup_symbol(op[i].op.vary.p->name) == NULL) add_symbol(op[i].op.vary.p->name, SYM_VALUE, 0);

        //printf("%s\n", op[i].op.vary.p->name);

        for(int f = (int)op[i].op.vary.start_frame; f <= (int)op[i].op.vary.end_frame; f++){

          changed = 0;

          curr = knobs[f];

          if(curr == NULL){
            knobs[f] = malloc(sizeof(struct vary_node));

            strcpy(knobs[f]->name,op[i].op.vary.p->name);
            knobs[f]->value = currentVal;
            knobs[f]->next = NULL;
          }
          else {
            while(curr->next != NULL){
              if(!strcmp(curr->name,op[i].op.vary.p->name)){
                curr->value = currentVal;
                changed = 0;
              }
              curr = curr->next;
            }

            if(!changed && curr->next == NULL){
              curr->next = malloc(sizeof(struct vary_node));

              strcpy(curr->next->name, op[i].op.vary.p->name);
              curr->next->value = currentVal;
              curr->next->next = NULL;
            }

            
          }

          currentVal += valChange;
        }

        break;

      case TWEEN:

        //print_symtab();

        curr_tween = lookup_symbol(op[i].op.tween.knob_list0->name)->s.v;
        //curr_tween = curr_tween->next;
        //if(curr_tween->next != NULL) printf("Test\n");

        while(curr_tween != NULL){

          //printf("%s %lf\n", curr_tween->name, curr_tween->value);

          startKnob = curr_tween;

          endKnob = lookup_symbol(op[i].op.tween.knob_list1->name)->s.v;

          if(strcmp(endKnob->name,startKnob->name) != 0){
            while (!strcmp(endKnob->name,startKnob->name)) endKnob = endKnob->next;
          }

          startVal = startKnob->value;
          endVal = endKnob->value;

          valChange = (endVal - startVal)/(op[i].op.tween.end_frame - op[i].op.tween.start_frame);
          currentVal = startVal;

          if(lookup_symbol(startKnob->name) == NULL) add_symbol(startKnob->name, SYM_VALUE, 0);

          for(int f = (int)op[i].op.tween.start_frame; f <= (int)op[i].op.tween.end_frame; f++){

            curr = knobs[f];

            if(curr == NULL){
              knobs[f] = malloc(sizeof(struct vary_node));

              strcpy(knobs[f]->name,startKnob->name);
              knobs[f]->value = currentVal;
              knobs[f]->next = NULL;
            }
            else {
              while(curr->next != NULL && !strcmp(curr->name,startKnob->name)){
                curr = curr->next;
              }


              if(!strcmp(curr->name,startKnob->name)){
                curr->value = currentVal;
              }
              else if(curr->next == NULL){
                curr->next = malloc(sizeof(struct vary_node));

                strcpy(curr->next->name, startKnob->name);
                curr->next->value = currentVal;
                curr->next->next = NULL;
              }     
            }

            currentVal += valChange;
          }


          curr_tween = curr_tween->next;
        }
    }
  }

  return knobs;
}

// void third_pass(struct matrix* p, struct matrix* t){
//   int i;

//   double step_3d;

// }

void my_main() {

  double frames_completion;
  double frames_change;

  int regCompile;

  regCompile = 0;

  regCompile = regcomp(&qF,"(([0-9]+) ){3}([0-9]+)", REG_EXTENDED);
  regCompile = regcomp(&qFT, "(([0-9]+/[0-9]+) ){3}([0-9]+/[0-9]+)", REG_EXTENDED);
  regCompile = regcomp(&qFN, "(([0-9]+//[0-9]+) ){3}([0-9]+//[0-9]+)", REG_EXTENDED);
  regCompile = regcomp(&qFTN, "(([0-9]+/[0-9]+/[0-9]+) ){3}([0-9]+/[0-9]+/[0-9]+)", REG_EXTENDED);

  regCompile = regcomp(&tF,"(([0-9]+) ){2}([0-9]+)", REG_EXTENDED);
  regCompile = regcomp(&tFT,"(([0-9]+/[0-9]+) ){2}([0-9]+/[0-9]+)", REG_EXTENDED);
  regCompile = regcomp(&tFN, "(([0-9]+//[0-9]+) ){2}([0-9]+//[0-9]+)", REG_EXTENDED);
  regCompile = regcomp(&tFTN, "(([0-9]+/[0-9]+/[0-9]+) ){2}([0-9]+/[0-9]+/[0-9]+)", REG_EXTENDED);

  if(regCompile){
    printf("Regex expressions failed to compile! exiting...\n");
    exit(1);
  }

  m = NULL;
  mI = NULL;

  struct vary_node ** knobs;
  struct vary_node * vn;
  struct vary_node* curr;
  first_pass();
  printf("First pass complete\n");
  knobs = second_pass();
  printf("Second pass complete\n");
  //print_materials();
  char frame_name[128];
  char meshName[512];
  int f;

  int i;
  int matID;
  struct matrix *tmp;
  struct matrix *texTmp;
  struct stack *systems;

  struct material* tmpMat;

  screen t;
  zbuffer zb;
  double step_3d = 50;
  double theta, xval, yval, zval;

  int shaderType = SHADER_PHONG;

  //Lighting values here for easy access
  color ambient;
  ambient.red = 50;
  ambient.green = 50;
  ambient.blue = 50;

  struct light* defaultLight = malloc(sizeof(struct light));
  struct light* tmpLight;
  defaultLight->l[0] = 0.5;
  defaultLight->l[1] = 0.75;
  defaultLight->l[2] = 1;

  defaultLight->c[RED] = 255;
  defaultLight->c[GREEN] = 255;
  defaultLight->c[BLUE] = 255;

  add_symbol("DefaultLight",SYM_LIGHT,defaultLight);

  double view[3];
  view[0] = 0;
  view[1] = 0;
  view[2] = 1;

  //default reflective constants if none are set in script file

  //constants are a pointer in symtab, using one here for consistency

  color g;
  g.red = 255;
  g.green = 255;
  g.blue = 255;

  struct kdTree* kd = NULL;

  frames_completion = 0;
  frames_change = 1.0/(double)num_frames;

  for(f = 0; f < num_frames; f++){

    //print_materials();

    systems = new_stack();
    ident(peek(systems));
    tmp = new_matrix(4, 1024);
    texTmp = new_matrix(4, 1024);

    matID = 0;
    clear_screen( t );
    clear_zbuffer(zb);

    curr = knobs[f];

    while(curr != NULL){
      lookup_symbol(curr->name)->s.value = curr->value;
      //printf("%s %d %lf %lf\n", curr->name,f, lookup_symbol(curr->name)->s.value, curr->value);
      curr = curr->next;
    }

    for (i=0;i<lastop;i++) {

      //printf("Operation %d\n", i);

      switch (op[i].opcode)
        {
        case SPHERE:
          // printf("Sphere: %6.2f %6.2f %6.2f r=%6.2f",
          //        op[i].op.sphere.d[0],op[i].op.sphere.d[1],
          //        op[i].op.sphere.d[2],
          //        op[i].op.sphere.r);
          if (op[i].op.sphere.constants != NULL) {
            //printf("\tconstants: %s",op[i].op.sphere.constants->name);
            //reflect = lookup_symbol(op[i].op.sphere.constants->name)->s.c;
            matID = find_material(op[i].op.sphere.constants->name)->id;
          }

          add_sphere(tmp, texTmp,
            (double)matID,
            op[i].op.sphere.d[0],
            op[i].op.sphere.d[1],
            op[i].op.sphere.d[2],
            op[i].op.sphere.r, step_3d);

          if (op[i].op.sphere.cs != NULL) {
            //printf("\tcs: %s",op[i].op.sphere.cs->name);
            matrix_mult( op[i].op.sphere.cs->s.m, tmp);
          } else {
            matrix_mult( peek(systems), tmp );
          }
          
          
          draw_polygons(tmp, texTmp, kd, t, zb, view, ambient,
                        shaderType);
          tmp->lastcol = 0;
          texTmp->lastcol = 0;
          //reflect = &white;
          matID = 0;

          break;
        case TORUS:
          // printf("Torus: %6.2f %6.2f %6.2f r0=%6.2f r1=%6.2f",
          //        op[i].op.torus.d[0],op[i].op.torus.d[1],
          //        op[i].op.torus.d[2],
          //        op[i].op.torus.r0,op[i].op.torus.r1);
          if (op[i].op.torus.constants != NULL) {
            //printf("\tconstants: %s",op[i].op.torus.constants->name);
            //reflect = lookup_symbol(op[i].op.sphere.constants->name)->s.c;
            matID = find_material(op[i].op.torus.constants->name)->id;
          }

          add_torus(tmp, texTmp,
            (double)matID,
            op[i].op.torus.d[0],
            op[i].op.torus.d[1],
            op[i].op.torus.d[2],
            op[i].op.torus.r0,op[i].op.torus.r1, step_3d);

          if (op[i].op.torus.cs != NULL) {
            //printf("\tcs: %s",op[i].op.torus.cs->name);
            matrix_mult(op[i].op.torus.cs->s.m, tmp);
          } else {
            matrix_mult( peek(systems), tmp );

          }

          
          draw_polygons(tmp, texTmp, kd, t, zb, view, ambient,
                        shaderType);
          tmp->lastcol = 0;
          texTmp->lastcol = 0;
          //reflect = &white;
          matID = 0;

          break;
        case BOX:
          // printf("Box: d0: %6.2f %6.2f %6.2f d1: %6.2f %6.2f %6.2f",
          //        op[i].op.box.d0[0],op[i].op.box.d0[1],
          //        op[i].op.box.d0[2],
          //        op[i].op.box.d1[0],op[i].op.box.d1[1],
          //        op[i].op.box.d1[2]);
          if (op[i].op.box.constants != NULL) {
            //printf("\tconstants: %s",op[i].op.box.constants->name);
            //reflect = lookup_symbol(op[i].op.sphere.constants->name)->s.c;
            matID = find_material(op[i].op.box.constants->name)->id;
          }

          add_box(tmp, texTmp,
            (double)matID,
            op[i].op.box.d0[0],op[i].op.box.d0[1],
            op[i].op.box.d0[2],
            op[i].op.box.d1[0],op[i].op.box.d1[1],
            op[i].op.box.d1[2]);

          if (op[i].op.box.cs != NULL) {
            //printf("\tcs: %s",op[i].op.box.cs->name);
            matrix_mult( op[i].op.box.cs->s.m, tmp);
          } else {
            matrix_mult( peek(systems), tmp );
          }

        
          draw_polygons(tmp, texTmp, kd, t, zb, view, ambient,
                        shaderType);
          tmp->lastcol = 0;
          texTmp->lastcol = 0;
          //reflect = &white;
          matID = 0;

          break;
        case PLANE:

          if(op[i].op.plane.constants != NULL) {
            //reflect = lookup_symbol(op[i].op.plane.constants->name)->s.c;
            matID = find_material(op[i].op.plane.constants->name)->id;
          }

          add_plane(tmp,
            op[i].op.plane.d[0],op[i].op.plane.d[1],op[i].op.plane.d[2],
            op[i].op.plane.w,op[i].op.plane.h);

          if(op[i].op.plane.cs != NULL){
            matrix_mult(op[i].op.plane.cs->s.m, tmp);
          } else {
            matrix_mult(peek(systems), tmp);
          }

          draw_polygons(tmp, texTmp, kd, t, zb, view, ambient, shaderType);
          tmp->lastcol = 0;
          texTmp->lastcol = 0;
          //reflect = &white;
          break;
        case CYLINDER:

          if (op[i].op.cylinder.constants != NULL){
            //reflect = lookup_symbol(op[i].op.cylinder.constants->name)->s.c;
            matID = find_material(op[i].op.cylinder.constants->name)->id;
          }

          add_cylinder(tmp, texTmp,
            (double)matID,
            op[i].op.cylinder.d[0],
            op[i].op.cylinder.d[1],
            op[i].op.cylinder.d[2],
            op[i].op.cylinder.r,
            op[i].op.cylinder.h,
            step_3d);

          if (op[i].op.cylinder.cs != NULL) {
            matrix_mult(op[i].op.cylinder.cs->s.m, tmp);
          } else {
            matrix_mult(peek(systems),tmp);
          }

          draw_polygons(tmp, texTmp, kd, t, zb, view, ambient, shaderType);

          tmp->lastcol = 0;
          texTmp->lastcol = 0;
          //reflect = &white;
          matID = 0;

          break;
        case MESH:

          //print_symtab();
          //sscanf(meshName,"%s%s",op[i].op.mesh.name,"_polygons");
          strcpy(meshName,op[i].op.mesh.name);
          strcat(meshName,"_polygons_");
          if(op[i].op.mesh.constants != NULL)strcat(meshName,op[i].op.mesh.constants->name);
          copy_matrix(lookup_symbol(meshName)->s.m,tmp);
          //print_matrix(tmp);
          //sscanf(meshName,"%s%s",op[i].op.mesh.name,"_textures");
          strcpy(meshName,op[i].op.mesh.name);
          strcat(meshName,"_textures_");
          if(op[i].op.mesh.constants != NULL)strcat(meshName,op[i].op.mesh.constants->name);
          copy_matrix(lookup_symbol(meshName)->s.m,texTmp);

          //sscanf(meshName,"%s%s",op[i].op.mesh.name,"_kdtree");
          strcpy(meshName,op[i].op.mesh.name);
          strcat(meshName,"_kdTree_");
          if(op[i].op.mesh.constants != NULL)strcat(meshName,op[i].op.mesh.constants->name);
          //kdPrint(lookup_symbol(meshName)->s.kd);
          //kd = lookup_symbol(meshName)->s.kd;
          kd = kdCreate();
          kdCopy(kd,lookup_symbol(meshName)->s.kd);

          //print_materials();
          //kd = kdNormalize(kd, view, ambient, reflect);
          //print_matrix(tmp);
          //kdPrint(kd);
          //printf("###########################################################\n");

          if(op[i].op.mesh.cs != NULL){
            matrix_mult(op[i].op.mesh.cs->s.m, tmp);
            kd = kdTransform(kd, op[i].op.mesh.cs->s.m);
          } else {
            matrix_mult(peek(systems),tmp);
            kd = kdTransform(kd, peek(systems));
          }

          //print_matrix(tmp);
          //kdPrint(kd);
          draw_polygons(tmp, texTmp, kd, t, zb, view, ambient, shaderType);
          tmp->lastcol = 0;
          texTmp->lastcol = 0;
          //reflect = &white;
          matID = 0;
          //texTmp = NULL;

          //peek(systems)->lastcol = 4;
          //print_matrix(peek(systems));
          //print_matrix(matrix_inverse(peek(systems)));

          break;
        case LINE:
          // printf("Line: from: %6.2f %6.2f %6.2f to: %6.2f %6.2f %6.2f",
          //        op[i].op.line.p0[0],op[i].op.line.p0[1],
          //        op[i].op.line.p0[2],
          //        op[i].op.line.p1[0],op[i].op.line.p1[1],
          //        op[i].op.line.p1[2]);
          if (op[i].op.line.constants != NULL) {
            //printf("\n\tConstants: %s",op[i].op.line.constants->name);
          }
          if (op[i].op.line.cs0 != NULL) {
            //printf("\n\tCS0: %s",op[i].op.line.cs0->name);
          }
          if (op[i].op.line.cs1 != NULL) {
            //printf("\n\tCS1: %s",op[i].op.line.cs1->name);
          }
          add_edge(tmp,
                   op[i].op.line.p0[0],op[i].op.line.p0[1],
                   op[i].op.line.p0[2],
                   op[i].op.line.p1[0],op[i].op.line.p1[1],
                   op[i].op.line.p1[2]);
          matrix_mult( peek(systems), tmp );
          draw_lines(tmp, t, zb, g);
          tmp->lastcol = 0;
          break;
        case MOVE:
          xval = op[i].op.move.d[0];
          yval = op[i].op.move.d[1];
          zval = op[i].op.move.d[2];
          //printf("Move: %6.2f %6.2f %6.2f", xval, yval, zval);
          if (op[i].op.move.p != NULL) {
            //printf("\tknob: %s",op[i].op.move.p->name);
            xval *= lookup_symbol(op[i].op.move.p->name)->s.value;
            yval *= lookup_symbol(op[i].op.move.p->name)->s.value;
            zval *= lookup_symbol(op[i].op.move.p->name)->s.value;
          }
          tmp = make_translate( xval, yval, zval );
          matrix_mult(peek(systems), tmp);
          copy_matrix(tmp, peek(systems));
          tmp->lastcol = 0;
          break;
        case SCALE:
          xval = op[i].op.scale.d[0];
          yval = op[i].op.scale.d[1];
          zval = op[i].op.scale.d[2];
          //printf("Scale: %6.2f %6.2f %6.2f", xval, yval, zval);
          if (op[i].op.scale.p != NULL) {
            //printf("\tknob: %s",op[i].op.scale.p->name);
            
            xval *= lookup_symbol(op[i].op.scale.p->name)->s.value;
            yval *= lookup_symbol(op[i].op.scale.p->name)->s.value;
            zval *= lookup_symbol(op[i].op.scale.p->name)->s.value;
          }
          tmp = make_scale( xval, yval, zval );
          matrix_mult(peek(systems), tmp);
          copy_matrix(tmp, peek(systems));
          tmp->lastcol = 0;
          break;
        case ROTATE:
          theta =  op[i].op.rotate.degrees * (M_PI / 180);
          if (op[i].op.rotate.p != NULL) {
            //printf("\tknob: %s",op[i].op.rotate.p->name);
            theta *= lookup_symbol(op[i].op.rotate.p->name)->s.value;
          }
          //printf("Rotate: axis: %6.2f degrees: %6.2f", op[i].op.rotate.axis, theta);

          if (op[i].op.rotate.axis == 0 )
            tmp = make_rotX( theta );
          else if (op[i].op.rotate.axis == 1 )
            tmp = make_rotY( theta );
          else
            tmp = make_rotZ( theta );

          matrix_mult(peek(systems), tmp);
          copy_matrix(tmp, peek(systems));
          tmp->lastcol = 0;
          break;
        case AMBIENT:

          ambient.red = op[i].op.ambient.c[0];
          ambient.green = op[i].op.ambient.c[1];
          ambient.blue = op[i].op.ambient.c[2];

          break;
        case SHADING:

          if(!strcmp(op[i].op.shading.p->name,"flat")) shaderType = SHADER_FLAT;
          if(!strcmp(op[i].op.shading.p->name,"gouraud")) shaderType = SHADER_GOURAUD;
          if(!strcmp(op[i].op.shading.p->name,"phong")) shaderType = SHADER_PHONG;
          if(!strcmp(op[i].op.shading.p->name,"wireframe")) shaderType = SHADER_WIREFRAME;

          break;
        case PUSH:
          //printf("Push");
          push(systems);
          break;
        case POP:
          //printf("Pop");
          pop(systems);
          break;
        case SET_LIGHT_LOCATION:

          tmpLight = lookup_symbol(op[i].op.set_light_location.p->name)->s.l;

          tmpLight->l[op[i].op.set_light_location.axis] = op[i].op.set_light_location.val;

          if(op[i].op.set_light_location.v != NULL){
            tmpLight->l[op[i].op.set_light_location.axis] *= lookup_symbol(op[i].op.set_light_location.v->name)->s.value;
          }

          break;
        case SAVE:
          if(num_frames <= 1){
            //printf("Save: %s",op[i].op.save.p->name);
            char finalName[256] = "";

            struct stat st = {0};

            if(stat("output",&st) == -1){
              mkdir("output",0700);
            }

            strcat(finalName,"output/");
            strcat(finalName,op[i].op.save.p->name);
            save_extension(t, finalName);
            printf("Image saved! Check the output folder\n");
          }
          break;
        case SAVE_COORDS:

          copy_matrix(peek(systems),lookup_symbol(op[i].op.save_coordinate_system.p->name)->s.m);

          break;
        case DISPLAY:
          if(num_frames <= 1){
            display(t);
            break;
          }
        }

      //print_symtab();
      //print_materials();
      //printf("\n");
      if(kd != NULL){
        kdFree(kd);
        kd = NULL;
      }

    } //end operation loop

    if(num_frames > 1){
      char fileName[256];
      if(f < 10) sprintf(fileName, "%s_000%d.png", name, f);
      else if(f < 100) sprintf(fileName, "%s_00%d.png", name, f);
      else if(f < 1000) sprintf(fileName, "%s_0%d.png", name, f);
      else sprintf(fileName, "%s_%d.png", name, f);
      save_extension(t, fileName);
    }

    free_stack( systems );
    free_matrix( tmp );
    free_matrix(texTmp);

    //print_materials();

    //delete_material_all();

    frames_completion += frames_change;
    printf("Animation %lf percent complete\n", frames_completion*100);

  }

  if(num_frames > 1){

    struct stat st = {0};

    if(stat("output",&st) == -1){
      mkdir("output",0700);
    }

    int status;

    int n = fork();


    if(n == 0){ //Child

      double delayTime;
      char fileArg[256];
      char delayArg[256];
      char finalFileArg[256];

      sprintf(fileArg, "%s_*",name);
      sprintf(finalFileArg, "output/%s.gif",name);

      delayTime = 1.7;
      sprintf(delayArg, "%.1f",delayTime);

      execlp("convert", "convert", "-delay", delayArg, fileArg, finalFileArg, NULL);
    } else {
      printf("Converting to gif...\n");
      waitpid(n, &status, 0);
    }

    n = fork();

    if(n == 0){
      char removeArg[256];

      for(f = 0; f < num_frames; f++){
        if(f < 10) sprintf(removeArg, "%s_000%d.png", name, f);
        else if(f < 100) sprintf(removeArg, "%s_00%d.png", name, f);
        else if(f < 1000) sprintf(removeArg, "%s_0%d.png", name, f);
        else sprintf(removeArg, "%s_%d.png", name, f);
        remove(removeArg);
      }

      exit(0);
    } else {
      printf("Cleaning up...\n");
      waitpid(n, &status, 0);

      printf("Drawing complete! Check the output folder\n");
    }
  }

  regfree(&qFTN);
  regfree(&qFN);
  regfree(&qFT);
  regfree(&qF);
  regfree(&tFTN);
  regfree(&tFN);
  regfree(&tFT);
  regfree(&tF);
}