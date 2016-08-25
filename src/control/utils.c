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
    float magnitude = magnitdeOfVector(vect);
    vect->x = vect->x/magnitude;
    vect->y = vect->y/magnitude;
}

float magnitdeOfVector(Vector2 *vect){
    float x = vect->x, y = vect->y;
    float power = x*x + y*y;
    return sqrt_f(power);
}

void vectorMulitplyByScalar(Vector2 *vect, float scalar){
    vect->x = vect->x * scalar;
    vect->y = vect->y * scalar;
}

float abs_c(float num){
    if(num >= 0){
        return num;
    } else return -num;
}

float dotProduct(Vector2 *vect1, Vector2 *vect2){
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "v1: %p, v2: %p", vect1, vect2);
  return vect1->x * vect1->y + vect1->y * vect2->y;
}

float sqrt_f( float num ){
    const uint MAX_STEPS = 40;
    const float MAX_ERROR = 0.001;

    float answer = num;
    float ans_sqr = answer * answer;
    uint step = 0;
    while((ans_sqr - num > MAX_ERROR) && (step++ < MAX_STEPS)) {
        answer = (answer + (num / answer)) / 2;
        ans_sqr = answer * answer;
    }
    return answer;
}
