#include "CollisionHelper.h"

static void findNormal(Edge2*, Vector2*);
static void get_normals_from_object (CollisionElement*, Vector2*, int*);
static int objects_overlap_in_normal(CollisionElement*, CollisionElement*, Vector2*);
static void get_min_max(MinMax*, CollisionElement*, Vector2*);


// Determines whether two objects are colliding with each other
int are_colliding(CollisionElement* object_a, CollisionElement* object_b) {
  int totalNumberOfEdges = object_a->numberOfEdges + object_b->numberOfEdges;
  int i = 0;

  //APP_LOG(APP_LOG_LEVEL_DEBUG, "INSIDE ARE COLIDING");

  Vector2 normals[totalNumberOfEdges];

  get_normals_from_object(object_a, normals, &i);
  get_normals_from_object(object_b, normals, &i);

  for( i = 0; i < totalNumberOfEdges; i++ ){
    Vector2 current_normal = normals[i];
	if(!objects_overlap_in_normal(object_a, object_b, &current_normal)){
		return 0;
	}
  }
  // If they overlapped on every possible normal, then that means that
  // both objects are colliding :|
  return 1;
}

int distance_to_collision(CollisionElement* object_a, CollisionElement* object_b){
  return 0; //stub
}

static int objects_overlap_in_normal(CollisionElement* object_a, CollisionElement* object_b, Vector2* normal){
  MinMax min_max_obj_a, min_max_obj_b;
  get_min_max(&min_max_obj_a, object_a, normal);
  get_min_max(&min_max_obj_b, object_b, normal);

  return !((min_max_obj_a.max < min_max_obj_b.min) || 
	   (min_max_obj_b.max < min_max_obj_a.min));

}

static void get_min_max(MinMax* res, CollisionElement* object, Vector2* normal){
  int current_object_index = 0;
  Edge2 current_edge = (object->array_of_edges[current_object_index]);
  int max = dotProduct(current_edge.a, normal);
  int min = dotProduct(current_edge.a, normal);

  for(; current_object_index < object->numberOfEdges; current_object_index++){
    current_edge = (object->array_of_edges[current_object_index]);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "idx: %i, cur: %p, curN: %i, cur_a: %p, cur_b: %p, cur_a_x: %f, cur_a_y: %f", current_object_index, 
	//		object, object->numberOfEdges, current_edge.a ,current_edge.b, current_edge.a->x, current_edge.a->y);
    int a_dot_prod = dotProduct(current_edge.a, normal);
    int b_dot_prod = dotProduct(current_edge.b, normal);
    max = (a_dot_prod > max) ? a_dot_prod : max;
    min = (a_dot_prod < min) ? a_dot_prod : min;
    max = (b_dot_prod > max) ? b_dot_prod : max;
    min = (b_dot_prod < min) ? b_dot_prod : min;
  }
  res->max = max;
  res->min = min;
}



static void findNormal(Edge2* edge, Vector2* result){
  result->x = - ( edge->a->x - edge->b->x );
  result->y = (edge->a->y - edge->b->y );
}

// Gets normals from the regular object
static void get_normals_from_object (CollisionElement* object, Vector2* normals, int* vector_counter){
  int current_object_index = 0;
  for(current_object_index = 0; current_object_index < object->numberOfEdges;
      (*vector_counter) += 1, current_object_index++){
    Vector2 current_normal = normals[(*vector_counter)];
    Edge2 current_edge = (object->array_of_edges[current_object_index]);
    findNormal(&current_edge, &current_normal);
  }
}
