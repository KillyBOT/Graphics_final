#ifndef CONVERT_H
#define CONVERT_H

#include <regex.h>

#include "ml6.h"
#include "matrix.h"
#include "draw.h"
#include "kdTree.h"

struct kdTree* convert(struct matrix* m, char* fileName);

#define BUFFER_SIZE 512

regex_t qF;
regex_t qFT;
regex_t qFN;
regex_t qFTN;

regex_t tF;
regex_t tFT;
regex_t tFN;
regex_t tFTN;

#endif