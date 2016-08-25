
#include "pebble.h"

#ifndef types_pin_peb_h
#define types_pin_peb_h
typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Edge2 {
  Vector2 *a;
  Vector2 *b;
} Edge2;

typedef Vector2 Point2;

typedef struct Ball {
    short radius;
    short x;
    short y;
    float dx;
    float dy;
    float _dt;
    float _tempY;
    float _gravity;

    void (* tick)(struct Ball*);
    void (* render)(struct Ball*, GContext*, int);
} Ball;

typedef struct CollisionElement {
  Edge2* array_of_edges;
  int numberOfEdges;
} CollisionElement;

typedef struct MinMax {
  int max;
  int min;
} MinMax;

typedef struct Map_Element{
    void *state;
    short height;
    short width;
    short offset_x;
    short offset_y;
    void (* render)(struct Map_Element*, GContext*, int);
    int (* collide)(struct Map_Element*, Ball*); // this will be called on every
                                                // tick of the clock so update
                                                // your state before clock
    void (* dealloc)(struct Map_Element*);
} Map_Element;

typedef struct TriggerState {
    int rotation;
    int transition_time;
    int up_time;
    void (* triggered)();
} TriggerState;

typedef struct LaunchAction {
  void (* launch)(struct Map_Element*, Ball*);
} LaunchAction;

#endif
