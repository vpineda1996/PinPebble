//
//  Map_Element.h
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//
#include "pebble.h"
#include "Ball.h"
#include "utils.h"
#include "CollisionHelper.h"
#include "../env.h"
#include <math.h>
#include "types.h"

#ifndef Map_Element_h
#define Map_Element_h

void element_init_default(Map_Element*);
void element_init_bump(Map_Element*);
void element_init_right_trigger(Map_Element*);
void element_init_left_trigger(Map_Element*);
void element_init_launcher_right(Map_Element*);
void element_init_launcher_left(Map_Element*);

#endif /* Map_Element_h */
