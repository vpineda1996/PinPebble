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
    short height;
    short width;
    short offset_x;
    short offset_y;
    void (* render)(struct Map_Element*, GContext*, int);
    int (* collide)(struct Map_Element*, Ball*); // this will be called on every
                                                // tick of the clock so update
                                                // your state before clock
} Map_Element;

void element_init_default(Map_Element*);

void element_init_circle(Map_Element*);
static void element_render_circle(Map_Element*, GContext*, int);
static int element_collide_circle(Map_Element*, Ball*);

void element_init_launcher(Map_Element*);
static void element_render_launcher(Map_Element*, GContext*, int);
static int element_collide_launcher(Map_Element*, Ball*);

#endif /* Map_Element_h */
