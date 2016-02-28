//
//  Map_Element.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Map_Element.h"

static void element_render_bump(Map_Element*, GContext*, int);
static int element_collide_bump(Map_Element*, Ball*);

static void element_render_launcher(Map_Element*, GContext*, int);
static int element_collide_launcher(Map_Element*, Ball*);

void element_init_default(Map_Element *elem){
    elem->height = 60;
    elem->width = 60;
    elem->offset_x = 30;
    elem->offset_y = 60;
}

// --------------------
// BASIC CIRCLE FUNCTIONS
// -------------------

void element_init_bump(Map_Element *bump){
    element_init_default(bump);
    bump->render = element_render_bump;
    bump->collide = element_collide_bump;
}

static void element_render_bump(Map_Element *this, GContext *ctx, int window_y_offset){
    if(within_bounds(window_y_offset, this)){
        int centerX = (this->offset_x + this->width / 2);
        int centerY = ((this->offset_y - window_y_offset) + this->height / 2);
        graphics_draw_circle(ctx, GPoint(centerX, centerY), this->width / 2);
        graphics_draw_circle(ctx, GPoint(centerX, centerY), this->width / 2 - 5);
    }
}

static int element_collide_bump(Map_Element *this, Ball *b){
    int elementCenterX = this->offset_x + this->width / 2;
    int elementCenterY = this->offset_y + this->height / 2;

    if(abs_c(b->x - elementCenterX) < this->width / 2 && abs_c(b->y - elementCenterY) < this->height / 2){ // inside circle , calculate new direction
        Vector2 direction2ball = {
            .x = (float)(b->x - elementCenterX),
            .y = (float)(b->y - elementCenterY)
        };

        Vector2 directionOfBall = {
            .x = (float)(b->dx),
            .y = (float)(b->dy)
        };

        float oldMagnitude = magnitdeOfVector(&directionOfBall);

        transformToUnitVector(&direction2ball);

        vectorMulitplyByScalar(&direction2ball, oldMagnitude);
        b->dx = ceil(direction2ball.x) == 0 ? floor(direction2ball.x) : ceil(direction2ball.x);
        b->dy = ceil(direction2ball.y) == 0 ? floor(direction2ball.y) : ceil(direction2ball.y);
        return true;

    }else return false;
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
        graphics_draw_rect(ctx, GRect(this->offset_x + 2, this->offset_y - window_y_offset + 2, this->width - 4, this->height - 2));
        graphics_context_set_fill_color(ctx, GColorFromRGB(150,150,150));
        graphics_fill_rect(ctx, GRect(this->offset_x, this->offset_y - window_y_offset + power*15, this->width, this->height - 15*power), 0, GCornerNone);
    }
}

static int element_collide_launcher(Map_Element *this, Ball *ball){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "launcher initiated operation");
  int power = (int) this->state;
  //if (ball->x + ball->radius > SCREEN_WIDTH - this->width && ball->y + ball->radius + 5 > SCREEN_HEIGHT - this->height) {
  if (true) {
    ball->dx = -.5;
    ball->dy = -25;
    ball->_tempY = -25;
    return true;
  }
  return false;
}
