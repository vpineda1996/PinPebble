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
#include <math.h>

typedef struct Vector2 {
    double x;
    double y;
} Vector2;

int within_bounds(int window_y_offset, Map_Element *element);
void transformToUnitVector(Vector2*);

#endif /* Map_h */
