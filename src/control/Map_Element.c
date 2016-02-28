//
//  Map_Element.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Map_Element.h"


void element_init_default(Map_Element *elem){
    elem->height = 20;
    elem->width = 20;
    elem->offset_x = 20;
    elem->offset_y = 20;
}

// --------------------
// BASIC CIRCLE FUNCTIONS
// -------------------

void element_init_circle(Map_Element *circle){
    element_init_default(circle);
    circle->render = element_render_circle;
    circle->tick = element_tick_circle;
    circle->collide = element_collide_circle;
}

static void element_render_circle(Map_Element *this, GContext *ctx, int window_y_offset){
    printf("it works %d\n", within_bounds(window_y_offset, this->offset_x, this->offset_y, this->width, this->height));
}

static void element_tick_circle(Map_Element  *this){
    // dont do anything
}

static void element_collide_circle(Map_Element *this, Ball *b){

}

// --------------------
// BASIC CIRCLE FUNCTIONS END
// -------------------
