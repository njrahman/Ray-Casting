#include "vec.h"


typedef struct { 
	vec_pt orig;
	vec_pt dir;	
} ray_t;

typedef struct {
	vec_pt center;
	double radius;
	
} sphere_t;

typedef struct {
	double R;
	double G;
	double B;
} color_t;

typedef struct object {
	sphere_t sphere;
	color_t color;
	struct object *next;
} obj_t;