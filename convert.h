#ifndef CONVERT_H
#define CONVERT_H

#include "ml6.h"
#include "matrix.h"
#include "draw.h"
#include "kdTree.h"

struct kdTree* convert(struct matrix* m, char* fileName);

#define BUFFER_SIZE 512

#endif