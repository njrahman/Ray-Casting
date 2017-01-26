#include "vec.h"
#include <stdio.h>
#include <math.h>


double vec_len(vec_pt v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

vec_pt normalize(vec_pt v) {
	double len;
	vec_pt normal_v;
	
	len = vec_len(v);

	normal_v.x = v.x/len;
	normal_v.y = v.y/len;
	normal_v.z = v.z/len;

	return normal_v;
}

double dot(vec_pt v1, vec_pt v2){

	return(v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

