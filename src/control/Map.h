//
//  Map.h
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "pebble.h"
#include "Map_Element.h"
#include "Ball.h"


#ifndef Map_h
#define Map_h

Map_Element *map_elements;
Ball *ball;

void map_init(Ball*);
void map_render(GContext *ctx, int window_y_offset);
void map_deinit();


#endif /* Map_h */
