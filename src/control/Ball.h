//
//  Ball.h
//
//
//  Created by Victor Pineda on 2016-02-27.
//
//

#include "../env.h"
#include "pebble.h"
#include "utils.h"

#ifndef Ball_h
#define Ball_h

typedef struct Ball {
    short radius;
    short x;
    short y;
    short dx;
    short dy;
    void (* tick)(struct Ball*);
    void (* render)(struct Ball*, GContext*, int);
} Ball;

void ball_init(Ball*);

#endif /* Ball_h */
