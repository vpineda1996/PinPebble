//
//  Map.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Map.h"
#define NUMBER_OF_MAP_ELEM 5

static Map_Element **map_elements;
static Ball *ball;
static Map_Element launcher_right, launcher_left, left_trigger, right_trigger, bumper_1;

void map_init(Ball* b){
    map_elements = calloc(NUMBER_OF_MAP_ELEM, sizeof(Map_Element*));
    ball = b;
    element_init_bump(&bumper_1);
    element_init_left_trigger(&left_trigger);
    element_init_right_trigger(&right_trigger);
    element_init_launcher_right(&launcher_right);
    element_init_launcher_left(&launcher_left);
    map_elements[0] = &bumper_1;
    map_elements[1] = &left_trigger;
    map_elements[2] = &right_trigger;
    map_elements[3] = &launcher_right;
    map_elements[4] = &launcher_left;
}

void map_render(GContext *ctx, int window_y_offset){
    int i;
    for (i = 0; i < NUMBER_OF_MAP_ELEM; i++) {
        map_elements[i]->render(map_elements[i], ctx, window_y_offset);
    }
}

void map_tick(){
    int i;
    for (i = 0; i < NUMBER_OF_MAP_ELEM; i++) {
        int ret = map_elements[i]->collide(map_elements[i], ball);
        if (ret){
            break;
        }
    }
}

void activateLeftTrigger(){
    ((TriggerState*)(left_trigger.state))->triggered(&left_trigger);
}

void activateRightTrigger(){
    ((TriggerState*)(right_trigger.state))->triggered(&right_trigger);
}

void launch_ball() {
  launcher_right.collide(&launcher_right, ball);
}
void map_deinit(){
    int i;
    for (i = 0; i < NUMBER_OF_MAP_ELEM; i++) {
        map_elements[i]->dealloc(map_elements[i]);
    }
    free(map_elements);
}
