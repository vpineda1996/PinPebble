//
//  Map_Element.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Map_Element.h"
#include <math.h>

static void element_render_bump(Map_Element*, GContext*, int);
static int element_collide_bump(Map_Element*, Ball*);

static void element_render_launcher(Map_Element*, GContext*, int);
static int element_collide_launcher(Map_Element*, Ball*);
static int element_collide_launcher_left(Map_Element*, Ball*);

// TRIGERS
static void element_render_right_trigger(Map_Element*, GContext*, int);
static int element_collide_right_trigger(Map_Element*, Ball*);

static void element_render_left_trigger(Map_Element*, GContext*, int);
static int element_collide_left_trigger(Map_Element*, Ball*);

static void element_triggered_trigger(Map_Element* this);

static void _update_on_tick_trigger_state(TriggerState *ts);
// END OF TRIGERS

static void element_dealloc_default(Map_Element*);
static void element_dealloc_trigger(Map_Element*);


void element_init_default(Map_Element *elem){
    elem->height = 60;
    elem->width = 60;
    elem->offset_x = 30;
    elem->offset_y = 60;
}

static void element_dealloc_default(Map_Element* this){
}

// --------------------
// BASIC CIRCLE FUNCTIONS
// -------------------

void element_init_bump(Map_Element *bump){
    element_init_default(bump);
    bump->render = element_render_bump;
    bump->collide = element_collide_bump;
    bump->dealloc = element_dealloc_default;
}

static void element_render_bump(Map_Element *this, GContext *ctx, int window_y_offset){
    if(within_bounds(window_y_offset, this)){
        graphics_context_set_fill_color(ctx, GColorFromRGB(0,64,175));
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
#define LAUNCHER_HEIGHT 45
#define LAUNCHER_WIDTH 20

void fire_ball(Map_Element *this, Ball *ball) {
  if (ball->y - ball->radius < this->offset_y + 15 && ball->y + ball->radius < this->offset_y + 15 && ball->x - ball->radius >= this->offset_x && ball->x + ball->radius <= this->offset_x + this->width) {
    ball->dx = 0;
    ball->dy = -25;
    ball->_tempY = -25;
  }
}

void element_init_launcher_right(Map_Element *launcher){
    launcher->height = LAUNCHER_HEIGHT;
    launcher->width = LAUNCHER_WIDTH;
    launcher->offset_x = MAP_WIDTH - launcher->width;
    launcher->offset_y = MAP_HEIGHT - launcher->height;

    LaunchAction *action = malloc(sizeof(LaunchAction));
    action->launch = fire_ball;
    launcher->state = action;
    launcher->render = element_render_launcher;
    launcher->collide = element_collide_launcher;
    launcher->dealloc = element_dealloc_default;
}

void element_init_launcher_left(Map_Element *launcher){
    launcher->height = LAUNCHER_HEIGHT;
    launcher->width = LAUNCHER_WIDTH;
    launcher->offset_x = 0;
    launcher->offset_y = MAP_HEIGHT - launcher->height;
    launcher->state = (void*) 2;
    launcher->render = element_render_launcher;
    launcher->collide = element_collide_launcher_left;
}

static void element_render_launcher(Map_Element *this, GContext *ctx, int window_y_offset){
    if(within_bounds(window_y_offset, this)){
        int power = 1;

        graphics_context_set_fill_color(ctx, GColorFromRGB(0,0,0));
        graphics_draw_rect(ctx, GRect(this->offset_x, this->offset_y - window_y_offset, this->width, this->height));
        graphics_draw_rect(ctx, GRect(this->offset_x + 2, this->offset_y - window_y_offset + 2, this->width - 4, this->height - 2));
        graphics_context_set_fill_color(ctx, GColorFromRGB(150,150,150));
        graphics_fill_rect(ctx, GRect(this->offset_x, this->offset_y - window_y_offset + power*15, this->width, this->height - 15*power), 0, GCornerNone);
    }
}


static int element_collide_launcher(Map_Element *this, Ball *ball){
  int power = (int) this->state;

  // go inside from center
  if (ball->y + ball->radius > this->offset_y && ball->x + ball->radius > this->offset_x && ball->x + ball->radius < this->offset_x) {
    if (ball->x - ball->radius < this->offset_x) {
      ball->x = this->offset_x;
    } else if (ball->x + ball->radius > this->offset_x + this->width) {
      ball->x = this->offset_x + this->width - ball->radius;
    } else {
      // unexpected ?
    }
    ball->dx = -ball->dx;

    if (ball->y + ball->radius > this->offset_y + (int)this->state * 15) {
      return true;
    }
  } else if (ball->x - ball->radius < this->offset_x && ball->x + ball->radius > this->offset_x && ball->y > this->offset_y) {
    // reflect back to right side
    ball->x = this->offset_x - ball->radius - 1;
    ball->dx = -ball->dx;
    return true;
  }
  //if (ball->x + ball->radius > SCREEN_WIDTH - this->width && ball->y + ball->radius + 5 > SCREEN_HEIGHT - this->height) {
  return false;
}

static int element_collide_launcher_left(Map_Element *this, Ball *ball){
  int power = (int) this->state;
  //if (ball->x + ball->radius > SCREEN_WIDTH - this->width && ball->y + ball->radius + 5 > SCREEN_HEIGHT - this->height) {


  // go inside from center
  if (ball->y + ball->radius > this->offset_y && ball->x + ball->radius > this->offset_x && ball->x < this->offset_x + this->width) {
    if (ball->x - ball->radius < this->offset_x) {
      ball->x = this->offset_x;
    } else if (ball->x + ball->radius > this->offset_x + this->width) {
      ball->x = this->offset_x + this->width - ball->radius;
    }
    ball->dx = -ball->dx;

    if (ball->y + ball->radius > this->offset_y + (int)this->state * 15) {
      ball->dx = 0;
      ball->dy = -25;
      ball->_tempY = -25;
      return true;
    }
  } else if (ball->x - ball->radius < this->offset_x + this->width && ball->x + ball->radius > this->offset_x + this->width && ball->y > this->offset_y) {
    // reflect back to right side
    ball->x = this->offset_x + this->width + ball->radius + 1;
    ball->dx = -ball->dx;
    return true;
  }

  return false;
}

// -----------------------------------------------------------------------------
// TRIGGERS
// -----------------------------------------------------------------------------
#define TRIGGER_WIDTH 45
#define TRIGGER_HEIGHT 25
#define SIDE_OFFSET LAUNCHER_WIDTH
#define SPACING 1
#define TIME_UP_TRIGGER 10
#define TIME_TRANSITION_TRIGGER 8
#define ANGLE_TRIGGER (0x10000 / 8)
#define STEPS_ANGLE_TRIGGER (0x10000 / 8) / TIME_TRANSITION_TRIGGER

void element_init_right_trigger(Map_Element* this){
    this->height = TRIGGER_HEIGHT;
    this->width = TRIGGER_WIDTH;
    this->offset_x = MAP_WIDTH - SIDE_OFFSET - SPACING;
    this->offset_y = MAP_HEIGHT - this->height * 2;
    this->render = element_render_right_trigger;
    this->collide = element_collide_right_trigger;
    this->dealloc = element_dealloc_trigger;
    TriggerState *ts = malloc(sizeof(TriggerState));
    ts->rotation = 0;
    ts->triggered = element_triggered_trigger;
    ts->transition_time = 0;
    ts->up_time = 0;
    this->state = (void*) ts;
}

void element_init_left_trigger(Map_Element* this){
    this->height = TRIGGER_HEIGHT;
    this->width = TRIGGER_WIDTH;
    this->offset_x = SIDE_OFFSET + SPACING;
    this->offset_y = MAP_HEIGHT - this->height * 2;
    this->render = element_render_left_trigger;
    this->collide = element_collide_left_trigger;
    this->dealloc = element_dealloc_trigger;
    TriggerState *ts = malloc(sizeof(TriggerState));
    ts->rotation = 0;
    ts->triggered = element_triggered_trigger;
    ts->transition_time = 0;
    ts->up_time = 0;
    this->state = (void*) ts;
}

static void element_triggered_trigger(Map_Element* this){
    ((TriggerState *)(this->state))->transition_time = TIME_TRANSITION_TRIGGER;
    ((TriggerState *)(this->state))->up_time = TIME_UP_TRIGGER;
}

static void element_render_right_trigger(Map_Element* this, GContext* ctx, int window_y_offset){
    TriggerState *ts = (TriggerState *) this->state;
    _update_on_tick_trigger_state(ts);
    GPoint path[] = {GPoint(0,0), GPoint(0,TRIGGER_HEIGHT), GPoint(-TRIGGER_WIDTH, TRIGGER_HEIGHT)};
    GPath il = (GPath) {
        .num_points = 3,
        .points = path,
        .rotation = ts->rotation,
        .offset = GPoint(this->offset_x, this->offset_y - window_y_offset)
    };
    gpath_draw_filled(ctx,&il);
}

static int element_collide_right_trigger(Map_Element* this, Ball* b){
  TriggerState *ts = (TriggerState*) this->state;
  int x1 = this->offset_x, y1 = this->offset_y;

  int x = (cos_lookup(ts->rotation) * TRIGGER_WIDTH) / TRIG_MAX_RATIO + x1;
  int y = (sin_lookup(ts->rotation) *TRIGGER_HEIGHT) / TRIG_MAX_RATIO + y1;


  float gradient = (y - y1) / (x - x1);
  float c = y1 - gradient * x1;
  float result = gradient * b->x + c;

    APP_LOG(APP_LOG_LEVEL_DEBUG, "%i %i %i", (int)result, b->y, (int) gradient);
  if (result - b->y  <= 5 && result - b->y >= 0 && b->x > x && b->x < x1) {
    Vector2 direction2ball = {
      .x = (float)(b->x - this->offset_x + this->width),
      .y = (float)(b->y - y1)
    };

    Vector2 directionOfBall = {
      .x = (float)(b->dx),
      .y = (float)(b->dy)
    };

    float oldMagnitude = magnitdeOfVector(&directionOfBall);

    transformToUnitVector(&direction2ball);

    vectorMulitplyByScalar(&direction2ball, oldMagnitude);
    b->dx = ceil(direction2ball.x) == 0 ? floor(direction2ball.x) : ceil(direction2ball.x);
    b->dy = -10;
    return true;
  }
  return false;
}

static void element_render_left_trigger(Map_Element* this, GContext* ctx, int window_y_offset){
    TriggerState *ts = (TriggerState *) this->state;
    _update_on_tick_trigger_state(ts);
    GPoint path[] = {GPoint(0,0), GPoint(0,TRIGGER_HEIGHT), GPoint(TRIGGER_WIDTH, TRIGGER_HEIGHT)};
    GPath il = (GPath) {
        .num_points = 3,
        .points = path,
        .rotation = -ts->rotation,
        .offset = GPoint(this->offset_x, this->offset_y - window_y_offset)
    };
    gpath_draw_filled(ctx,&il);
}

static int element_collide_left_trigger(Map_Element* this, Ball* b){
  TriggerState *ts = (TriggerState*) this->state;
  int x1 = this->offset_x, y1 = this->offset_y;

  int x = (cos_lookup(ts->rotation) * TRIGGER_WIDTH) / TRIG_MAX_RATIO + x1;
  int y = (sin_lookup(ts->rotation) *TRIGGER_HEIGHT) / TRIG_MAX_RATIO + y1;


  float gradient = (y - y1) / (x - x1);
  float c = y1 - gradient * x1;
  float result = gradient * b->x + c;

    APP_LOG(APP_LOG_LEVEL_DEBUG, "%i %i %i", (int)result, b->y, (int) gradient);
  if (result - b->y  <= 5 && result - b->y >= 0 && b->x < x && b->x > x1) {
    Vector2 direction2ball = {
      .x = (float)(b->x - this->offset_x + this->width),
      .y = (float)(b->y - y1)
    };

    Vector2 directionOfBall = {
      .x = (float)(b->dx),
      .y = (float)(b->dy)
    };

    float oldMagnitude = magnitdeOfVector(&directionOfBall);

    transformToUnitVector(&direction2ball);

    vectorMulitplyByScalar(&direction2ball, oldMagnitude);
    b->dx = ceil(direction2ball.x) == 0 ? floor(direction2ball.x) : ceil(direction2ball.x);
    b->dy = -10;
    return true;
  }


  return false;
}

static void element_dealloc_trigger(Map_Element* this){
    free(this->state);
}

static void _update_on_tick_trigger_state(TriggerState *ts){
    if(ts->up_time > 0){
        if(ts->transition_time > 0){
            ts->rotation = STEPS_ANGLE_TRIGGER * (TIME_TRANSITION_TRIGGER - ts->transition_time);
            ts->transition_time--;
        }else ts->up_time--;
    }else ts->rotation = sin_lookup(0);
}
