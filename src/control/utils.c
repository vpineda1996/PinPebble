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

float transformToUnitVector(Vector2* vect){
    float magnitude = magnitdeOfVector(vect);
	vectorMulitplyByScalar(vect, 1.0f / magnitude);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "magnitude: %i, vect.x: %i, vect.y:%i", 
	//		(int)magnitude, (int) vect->x, (int) vect->y);
	return magnitude;
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
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "v1.x: %i, v1.y: %i, v2.x:%i, v2.y:%i", 
  //		  (int)vect1->x, (int)vect1->y, 
  //		  (int)vect2->x, (int)vect2->y);
  return (vect1->x * vect2->x) + (vect1->y * vect2->y);
}

float sqrt_f( float num ){
    const int MAX_STEPS = 40;
    const float MAX_ERROR = 0.001;

    float answer = num;
    float ans_sqr = answer * answer;
    int step = 0;
    while((ans_sqr - num > MAX_ERROR) && (step++ < MAX_STEPS)) {
        answer = (answer + (num / answer)) / 2;
        ans_sqr = answer * answer;
    }
    return answer;
}
