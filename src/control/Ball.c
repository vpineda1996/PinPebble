//
//  Ball.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Ball.h"
#include <math.h>

static void ball_tick(Ball*);
static void ball_render(Ball* this, GContext *ctx, int window_y_offset);

void ball_init(Ball* this){
    this->tick = ball_tick;
    this->render = ball_render;
    this->radius = 6;
    this->x = SCREEN_WIDTH - this->radius ;
    this->y = SCREEN_HEIGHT - this->radius;
    this->dx = -2;
    this->dy = -2;
}

static void ball_tick(Ball* this){
    int tempX = this->x + this->dx;
    int tempY = this->y + this->dy;
    if(tempX > MAP_WIDTH - this->radius || tempX < this->radius){
        if (tempX > MAP_WIDTH - this->radius){
            tempX = MAP_WIDTH - this->radius;
        }else {
            tempX = this->radius + abs(tempX);
        }
        this->dx= -this->dx;
    }

    if(tempY > MAP_HEIGHT - this->radius || tempY < this->radius){
        if (tempY > MAP_HEIGHT - this->radius){
            tempY = MAP_HEIGHT - this->radius;
        }else {
            tempY = this->radius + abs(tempY);
        }
        this->dy= -this->dy;
    }
    this->x = tempX;
    this->y = tempY;
}

static void ball_render(Ball* this, GContext *ctx, int window_y_offset){
    int centerX = this->x;
    int centerY = (this->y - window_y_offset);
    graphics_fill_circle(ctx, GPoint(centerX, centerY), this->radius);
}
