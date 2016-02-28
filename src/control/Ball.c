//
//  Ball.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Ball.h"

static void ball_tick(Ball*);
static void ball_render(Ball* this, GContext *ctx, int window_y_offset);

void ball_init(Ball* this){
    this->tick = ball_tick;
    this->render = ball_render;
    this->radius = 6;
    this->x = SCREEN_WIDTH - this->radius * 2 ;
    this->y = SCREEN_HEIGHT - this->radius * 2;
    this->dx = -5;
    this->dy = -5;
}

static void ball_tick(Ball* this){
    int tempX = this->x + this->dx;
    int tempY = this->y + this->dy;
    if(tempX > MAP_WIDTH || tempX < 0){
        if (tempX > MAP_WIDTH){
            tempX = tempX - (MAP_WIDTH - tempX);
        }else {
            tempX = -tempX;
        }
        this->dx= -this->dx;
    }

    if(tempY > MAP_HEIGHT || tempY < 0){
        if (tempY > MAP_HEIGHT){
            tempY = tempY - (MAP_HEIGHT - tempY);
        }else {
            tempY = -tempY;
        }
        this->dy= -this->dy;
    }
}

static void ball_render(Ball* this, GContext *ctx, int window_y_offset){
    int centerX = (this->x - this->radius);
    int centerY = ((this->y - window_y_offset) - this->radius);
    graphics_fill_circle(ctx, GPoint(centerX, centerY), this->radius);
}
