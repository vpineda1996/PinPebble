//
//  utils.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "utils.h"

int within_bounds(int window_y_offset, Map_Element *element){
    short element_x_offset = element->offset_x,
        element_y_offset = element->offset_y,
        width = element->width,
        height = element->height;
    if(element_x_offset > MAP_WIDTH || element_x_offset < 0){
        return element_x_offset - SCREEN_WIDTH + width > 0;
    }else if((element_y_offset - window_y_offset) > SCREEN_HEIGHT || element_y_offset < 0){ // if it starts at the outside
        return (element_y_offset - window_y_offset) - SCREEN_HEIGHT - height > 0;
    }return true;
}
