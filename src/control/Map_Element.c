//
//  Map_Element.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Map_Element.h"
#include "../env.h"

static void element_render_circle(Map_Element*, GContext*, int);
static int element_collide_circle(Map_Element*, Ball*);

void element_init_default(Map_Element *elem){
    elem->height = 30;
    elem->width = 30;
    elem->offset_x = 0;
    elem->offset_y = 0;
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
    if(within_bounds(window_y_offset, this)){
        int centerX = (this->offset_x + this->width / 2);
        int centerY = ((this->offset_y - window_y_offset) + this->height / 2);
        graphics_draw_circle(ctx, GPoint(centerX, centerY), this->width / 2);
        graphics_draw_circle(ctx, GPoint(centerX, centerY), this->width / 2 - 5);
    }
}

static int element_collide_circle(Map_Element *this, Ball *b){
    return 0;
}

// --------------------
// BASIC LAUNCHER FUNCTIONS
// -------------------

void element_init_launcher(Map_Element *launcher){
    launcher->height = 45;
    launcher->width = 20;
    launcher->offset_x = MAP_WIDTH - launcher->width;
    launcher->offset_y = MAP_HEIGHT - launcher->height;
    launcher->state = (void*) 1;
    launcher->render = element_render_launcher;
    launcher->collide = element_collide_launcher;
}

static void element_render_launcher(Map_Element *this, GContext *ctx, int window_y_offset){
    if(within_bounds(window_y_offset, this)){
        int power = (int) this->state;

        graphics_context_set_fill_color(ctx, GColorFromRGB(0,0,0));
        graphics_draw_rect(ctx, GRect(this->offset_x, this->offset_y - window_y_offset, this->width, this->height));
        graphics_context_set_fill_color(ctx, GColorFromRGB(150,150,150));
        graphics_fill_rect(ctx, GRect(this->offset_x, this->offset_y - window_y_offset + power*15, this->width, this->height - 15*power), 0, GCornerNone);
    }
}

static int element_collide_launcher(Map_Element *this, Ball *b){
  int power = (int) this->state;
  return false;
}
