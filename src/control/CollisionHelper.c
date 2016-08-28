#include "CollisionHelper.h"

static float findNormal(Edge2*, Vector2*);
static void get_normals_from_object (CollisionElement*, Vector2*, int*);
static int objects_overlap_in_normal(CollisionElement*, CollisionElement*, Vector2*);
static void get_min_max(MinMax*, CollisionElement*, Vector2*);
static void get_min_max_poly(MinMax*, CollisionElement*, Vector2*);
static void get_min_max_circ(MinMax*, CollisionElement*, Vector2*);

// Determines whether two objects are colliding with each other
int are_colliding(CollisionElement* object_a, CollisionElement* object_b) {
  int totalNumberOfEdges = object_a->numberOfEdges + object_b->numberOfEdges;
  int i = 0;

  //APP_LOG(APP_LOG_LEVEL_DEBUG, "INSIDE ARE COLIDING");

  Vector2 normals[totalNumberOfEdges];

  get_normals_from_object(object_a, normals, &i);
  get_normals_from_object(object_b, normals, &i);

  for( i = 0; i < totalNumberOfEdges; i++ ){
    Vector2 *current_normal = &normals[i];
	if(!objects_overlap_in_normal(object_a, object_b, current_normal)){
		return 0;
	}
  }
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Collison detected!");
  // If they overlapped on every possible normal, then that means that
  // both objects are colliding :|
  return 1;
}

int distance_to_collision(CollisionElement* object_a, CollisionElement* object_b){
  return 0; //stub
}

void calc_bounce_vector(Vector2* direction, Edge2* edge, Vector2* res){
	Vector2 n;
	// Find the edge's normal 
	findNormal(edge, &n);
	Vector2 v = n; // copy vector
	APP_LOG(APP_LOG_LEVEL_DEBUG, "n.x: %i, n.y:%i", (int) (n.x * 100) , (int) (n.y * 100));
	// Project the velocity on the normal to break velocity into an orthogonal
	// and parallel vector
	// We multiply by two to avoid doing that later on because the parallel
	// vector to the edge is direction - v, then we know that the bouce
	// vector is (direction - v) - v
	float scalar = 2 * dotProduct(direction, &n);
	vectorMulitplyByScalar(&v, scalar);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "scalar: %i, dot: %i",
			(int) (scalar * 100), (int) (dotProduct(direction, &n) *100));

	res->x = direction->x - v.x;
	res->y = direction->y - v.y;
	APP_LOG(APP_LOG_LEVEL_DEBUG, "direction.x: %i, direction.y: %i, v.x: %i, v.y: %i, res.x: %i, res.y: %i",
			(int) (direction->x * 100), (int) (direction->y *100),
			(int) (v.x * 100), (int) (v.y * 100),
			(int) (res->x *100), (int) (res->y * 100));
    APP_LOG(APP_LOG_LEVEL_DEBUG, "e.a.x: %i, e.a.y: %i, e.b.x: %i, e.b.y: %i",
			(int) (edge->a->x * 100), (int) (edge->a->y *100),
			(int) (edge->b->x * 100), (int) (edge->b->y * 100));
}

static int objects_overlap_in_normal(CollisionElement* object_a, CollisionElement* object_b, Vector2* normal){
  MinMax min_max_obj_a, min_max_obj_b;
  get_min_max(&min_max_obj_a, object_a, normal);
  get_min_max(&min_max_obj_b, object_b, normal);

  int res = !((min_max_obj_a.max < min_max_obj_b.min) || 
	   (min_max_obj_b.max < min_max_obj_a.min));
  
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "a.max: %i, a.min: %i, b.max: %i, b.min: %i, res: %i",
  //	  min_max_obj_a.max,
  //	  min_max_obj_a.min,
  //	  min_max_obj_b.max,
  //	  min_max_obj_b.min,
  //	  res);
  return res;
}

static void get_min_max(MinMax* res, CollisionElement* object, Vector2* normal){
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "normal.x: %d, normal.y:%d", (int)normal->x, (int)normal->y);
	if(object->isCircle){
	  get_min_max_circ(res, object, normal);
	}else {
      get_min_max_poly(res, object, normal);
	}
}

static void get_min_max_poly(MinMax* res, CollisionElement* object, Vector2* normal){
  int current_object_index = 0;
  Edge2 *current_edge = &(object->array_of_edges[current_object_index]);
  float max = dotProduct(current_edge->a, normal);
  float min = dotProduct(current_edge->a, normal);

  for(; current_object_index < object->numberOfEdges; current_object_index++){
    current_edge = &(object->array_of_edges[current_object_index]);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "idx: %i, cur: %p, curN: %i, cur_a_x: %d, cur_a_y: %d, cur_b_x: %d, cur_b_y: %d", current_object_index, 
	//		object, object->numberOfEdges, 
	//		(int)current_edge->a->x, (int)current_edge->a->y, 
	//		(int)current_edge->b->x, (int)current_edge->b->y);
    float a_dot_prod = dotProduct(current_edge->a, normal);
    float b_dot_prod = dotProduct(current_edge->b, normal);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "a.dot:%i, b.dot:%i, n.x:%i, n.y:%i ",
	//		(int) a_dot_prod, (int) b_dot_prod, (int) normal->x, (int)normal->y );
    max = (a_dot_prod > max) ? a_dot_prod : max;
    min = (a_dot_prod < min) ? a_dot_prod : min;
    max = (b_dot_prod > max) ? b_dot_prod : max;
    min = (b_dot_prod < min) ? b_dot_prod : min;
  }

  res->max = max;
  res->min = min;
  //APP_LOG(APP_LOG_LEVEL_DEBUG,"res_poly_max: %i, res_poly_min: %i", res->max, res->min);
}

static void get_min_max_circ(MinMax* res, CollisionElement* object, Vector2* normal){
  Vector2 center_vector = {
	.x = object->circle->x,
	.y = object->circle->y
  };
  float center = dotProduct(&center_vector, normal);
  res->min = center - object->circle->radius;
  res->max = center + object->circle->radius;
  //APP_LOG(APP_LOG_LEVEL_DEBUG,"res_circ_max: %i, res_circ_min: %i", res->max, res->min);
}

static float findNormal(Edge2* edge, Vector2* result){
  result->x = - ( edge->b->x - edge->a->x );
  result->y = (edge->b->y - edge->a->y );
  float edge_mag = transformToUnitVector(result);
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "n.x: %i, n.y:%i",
  //		  (int)result->x, (int)result->y);
  return edge_mag;
}

// Gets normals from the regular object
static void get_normals_from_object (CollisionElement* object, Vector2* normals, int* vector_counter){
  int current_object_index = 0;
  for(current_object_index = 0; current_object_index < object->numberOfEdges;
      (*vector_counter) += 1, current_object_index++){
    Vector2 *current_normal = &normals[(*vector_counter)];
    Edge2 *current_edge = &(object->array_of_edges[current_object_index]);
    findNormal(current_edge, current_normal);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "vect_count: %i, normal_ptr:%p, c_n.x: %i, c_n.y:%i",
   	//	  (*vector_counter), current_normal, (int)current_normal->x, (int)current_normal->y);
  }
}
