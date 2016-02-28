//
//  Map.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Map.h"
#define NUMBER_OF_MAP_ELEM 1

static Map_Element *map_elements;
static Ball *ball;
static Map_Element launcher;

void map_init(Ball* b){
    map_elements = calloc(NUMBER_OF_MAP_ELEM, sizeof(Map_Element));
    ball = b;
    element_init_circle(&map_elements[0]);
    element_init_launcher(&launcher);
}

void map_render(GContext *ctx, int window_y_offset){
    int i;
    launcher.render(&launcher, ctx, window_y_offset);
    for (i = 0; i < NUMBER_OF_MAP_ELEM; i++) {
        map_elements[i].render(&map_elements[i], ctx, window_y_offset);
    }
}

void map_tick(){
    int i;
    for (i = 0; i < NUMBER_OF_MAP_ELEM; i++) {
        int ret = map_elements[i].collide(&map_elements[i], ball);
        if (ret){
            break;
        }
    }
}

void map_deinit(){
    free(map_elements);
}
