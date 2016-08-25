//
// CollisionHelper.h
//

#include "pebble.h"
#include "utils.h"
#include "../env.h"
#include "types.h"

#ifndef Collision_Helper_h
#define Collision_Helper_h

int are_colliding(CollisionElement*, CollisionElement*);
int distance_to_collision(CollisionElement*, CollisionElement*);

#endif
