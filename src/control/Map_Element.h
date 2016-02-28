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


#ifndef Map_Element_h
#define Map_Element_h

typedef struct Map_Element{
    void *state;
    int height;
    int width;
    int offset_x;
    int offset_y;
    void (* render)(struct Map_Element*, GContext*, int);
    void (* tick)(struct Map_Element*);
    void (* collide)(struct Map_Element*, Ball*);
} Map_Element;

void element_init_default(Map_Element*);

void element_init_circle(Map_Element*);
static void element_render_circle(Map_Element*, GContext*, int);
static void element_tick_circle(Map_Element*);
static void element_collide_circle(Map_Element*, Ball*);


#endif /* Map_Element_h */
