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
    this->x = this->radius * 2;
    this->y = SCREEN_HEIGHT / 2 ;
    this->dx = -2;
    this->dy = -1;
    this->_dt = .2;
    this->_tempY = 0;
    this->_gravity = 3;
}

static int applyGravity(Ball *this) {
  if (this->dy == 0) return this->y;
  float _tempY = this->_tempY + this->_dt * this->_gravity;
  float dy = _tempY * this->_dt + .5 * this->_gravity * this->_dt * this->_dt;
  this->_tempY = _tempY > 20 ? 20: _tempY;
  this->dy = dy > 3 ? 3 : dy;

  return this->dy + this->y;
}

static void ball_tick(Ball* this){
    int tempX = this->x + this->dx;
    int tempY = applyGravity(this);

    if(tempX > MAP_WIDTH - this->radius || tempX < this->radius){
        if (tempX > MAP_WIDTH - this->radius){
            tempX = MAP_WIDTH - this->radius;
        } else {
            tempX = this->radius + abs(tempX);
        }
        this->dx= -this->dx;
    }

    if(tempY > MAP_HEIGHT - this->radius || tempY < this->radius){
        if (tempY > MAP_HEIGHT - this->radius){
            tempY = MAP_HEIGHT - this->radius;
            this->_tempY = this->dy < 2 ? 0 : -this->_tempY / 2;
        } else {
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
