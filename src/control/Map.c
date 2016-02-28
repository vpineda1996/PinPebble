//
//  Map.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "Map.h"
#define NUMBER_OF_MAP_ELEM 1

void map_init(Ball* b){
    map_elements = calloc(NUMBER_OF_MAP_ELEM, sizeof(Map_Element));
    ball = b;
    element_init_circle(&map_elements[0]);
}

void map_render(GContext *ctx, int window_y_offset){
    int i;
    for (i = 0; i < NUMBER_OF_MAP_ELEM; i++) {
        map_elements[i].render(&map_elements[i], ctx, window_y_offset);
    }
}

void map_deinit(){
    free(map_elements);
    free(ball);
}
