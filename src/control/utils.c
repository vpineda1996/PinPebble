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
    if(element_x_offset > MAP_WIDTH){
        return false;
    }else if(element_x_offset < 0){
        return element_x_offset + width > 0;
    }else if((element_y_offset - window_y_offset) > SCREEN_HEIGHT){ // if it starts at the outside
        return false;
    }else if(element_y_offset < 0){
        return (element_y_offset - window_y_offset) + height > 0;
    }return true;
}

void transformToUnitVector(Vector2* vect){
    double x = vect->x, y = vect->y;
    double power = x*x + y*y;
    double magnitude = sqrt(power);
    vect->x = vect->x/magnitude;
    vect->y = vect->y/magnitude;
}
