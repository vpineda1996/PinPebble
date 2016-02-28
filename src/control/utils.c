//
//  utils.c
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "utils.h"


#define MAP_HEIGHT 336
#define MAP_WIDTH 144
#define SCREEN_WIDTH 168
#define SCREEN_HEIGHT 144

#define true 1
#define false 0

int within_bounds(int window_y_offset, int element_x_offset, int element_y_offset,
                    int width, int height){
    if(element_x_offset > MAP_WIDTH || element_x_offset < 0){
        return element_x_offset - SCREEN_WIDTH + width > 0;
    }else if((element_y_offset - window_y_offset) > SCREEN_HEIGHT || element_y_offset < 0){ // if it starts at the outside
        return (element_y_offset - window_y_offset) - SCREEN_HEIGHT - height > 0;
    }return true;
}
