//
//  utils.h
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#ifndef utils_h
#define utils_h

#include "Map_Element.h"
#include "../env.h"

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

int within_bounds(int window_y_offset, Map_Element *element);
void transformToUnitVector(Vector2*);
void negateVector(Vector2* vect);
float magnitdeOfVector(Vector2 *vect);
float dotProduct(Vector2 *vect1, Vector2 *vect2);
void add2VectorsAndSaveOnFirst(Vector2 *vect1, Vector2 *vect2);
void vectorMulitplyByScalar(Vector2 *vect, float scalar);

float abs_c(float num);
float sqrt_f(float);

#endif /* Map_h */
