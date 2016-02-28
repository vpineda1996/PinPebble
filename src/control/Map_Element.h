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
#include "../env.h"
#include <math.h>


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
    void (* dealloc)(struct Map_Element*);
} Map_Element;

typedef struct TriggerState {
    int rotation;
    int transition_time;
    int up_time;
    void (* triggered)();
} TriggerState;

void element_init_default(Map_Element*);
void element_init_bump(Map_Element*);
void element_init_right_trigger(Map_Element*);
void element_init_left_trigger(Map_Element*);
void element_init_launcher_right(Map_Element*);
void element_init_launcher_left(Map_Element*);

#endif /* Map_Element_h */
