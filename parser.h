#ifndef PARSER_H
#define PARSER_H

#include "symtab.h"
#include "matrix.h"

#define MAX_COMMANDS 512

extern int lastop;

#define Ka 0
#define Kd 1
#define Ks 2

struct command
{
  int opcode;
  union
  {
    struct {
      SYMTAB *p;
      SYMTAB *v;
      double l[4];
      double c[4];
    } light;
    struct {
      SYMTAB* p;
      double c[4];
    } ambient;
    struct {
      SYMTAB *p;
      /* each triple holds ka kd and ks for red green and blue
         respectively */
    } constants;
    struct {
      SYMTAB *p;
    } save_coordinate_system;
    struct {
      double eye[4],aim[4];
    } camera;
    struct {
      SYMTAB *constants;
      double d[4];
      double r;
      SYMTAB *cs;
    } sphere;
    struct {
      SYMTAB *constants;
      double d0[3];
      double d1[3];
      double d2[3];
      double d3[3];
      SYMTAB *p;
      SYMTAB *cs;
    } texture;
    struct {
      SYMTAB *constants;
      double d[4];
      double r0,r1;
      SYMTAB *cs;
    } torus;
    struct {
      SYMTAB* constants;
      double d[4];
      double r, h;
      SYMTAB *cs;
    } cylinder;
    struct {
      SYMTAB *constants;
      double d0[4],d1[4];
      SYMTAB *cs;
    } box;
    struct {
      SYMTAB *constants;
      double d[4];
      double w, h;
      SYMTAB* cs;
    } plane;
    struct {
      SYMTAB *constants;
      double p0[4],p1[4];
      SYMTAB *cs0,*cs1;
    } line;
    struct {
      SYMTAB *constants;
      char name[255];
      SYMTAB *cs;
    } mesh;
    struct {
      SYMTAB *p;
      double val;
    } set;
    struct {
      SYMTAB *p;
      SYMTAB *v;
      int axis;
      double val;
    } set_light_location;
    struct {
      SYMTAB *p;
      double c;
      double val;
    } set_light_color;
    struct {
      double d[4];
      SYMTAB *p;
    } move;
    struct {
      double d[4];
      SYMTAB *p;
    } scale;
    struct {
      double axis;
      double degrees;
      SYMTAB *p;
    } rotate;
    struct {
      SYMTAB *p;
    } basename;
    struct {
      SYMTAB *p;
    } save_knobs;
    struct {
      double start_frame, end_frame;
      SYMTAB *knob_list0;
      SYMTAB *knob_list1;
    } tween;
    struct {
      double num_frames;
    }frames;
    struct {
      SYMTAB *p;
      double start_frame, end_frame, start_val, end_val;
    } vary;
    struct {
      SYMTAB *p;
    } save;
    struct {
      SYMTAB *p;
    } shading;
    struct {
      double value;
    } setknobs;
    struct {
      double value;
    } focal;
  } op;
};



extern struct command op[MAX_COMMANDS];
//Code generator headers
int num_frames;
char name[128];

struct vary_node {

  char name[128];
  double value;
  struct vary_node *next;
};

void print_knobs();
void process_knobs();
void first_pass();
struct vary_node ** second_pass();
void print_pcode();
void my_main();
#endif
