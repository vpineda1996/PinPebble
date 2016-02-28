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
    elem->offset_x = -10;
    elem->offset_y = -10;
}

// --------------------
// BASIC CIRCLE FUNCTIONS
// -------------------

void element_init_circle(Map_Element *circle){
    element_init_default(circle);
    circle->render = element_render_circle;
    circle->collide = element_collide_circle;
}

static void element_render_circle(Map_Element *this, GContext *ctx, int window_y_offset){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Started rendering circle");
    if(within_bounds(window_y_offset, this)){
        APP_LOG(APP_LOG_LEVEL_DEBUG, "True");
        graphics_draw_circle(ctx, GPoint((this->offset_x + this->width / 2),
                                            ((this->offset_y - window_y_offset) + this->height / 2)), this->width/2);
    }
    APP_LOG(APP_LOG_LEVEL_DEBUG, "End render circle");
}

static int element_collide_circle(Map_Element *this, Ball *b){
    return 0;
}

// --------------------
// BASIC CIRCLE FUNCTIONS END
// -------------------
