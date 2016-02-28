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

void map_init();
void map_render(GContext*, int);
void map_deinit();


#endif /* Map_h */
