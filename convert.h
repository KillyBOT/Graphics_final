#ifndef CONVERT_H
#define CONVERT_H

#include "ml6.h"
#include "matrix.h"
#include "draw.h"
#include "kdTree.h"

struct matrix* convert(struct matrix* m, struct kdTree* kd, char* fileName);

#define BUFFER_SIZE 512

#endif