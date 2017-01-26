
#include <stdio.h>
#include "rc.h"
#include <math.h>
#include <stdlib.h>

vec_pt normalize(vec_pt v);

void read_objs(obj_t **list){
	
	obj_t *node; //Stores the info for each sphere
	double cx, cy, cz, rad; //The center coordinates and radius for the sphere
	double R, G, B; //The color of the sphere
	*list = NULL; //Clears the list in case there is any garbage
	
	while(scanf("%lf %lf %lf %lf %lf %lf %lf", &cx, &cy, &cz, &rad, &R, &G, &B) == 7){ //Reads the file, each value is a long float(double)
		
		node = (obj_t*) malloc(sizeof(obj_t)); // allocates memory for each object
		
		//Sets values
		node->sphere.center.x = cx;
		node->sphere.center.y = cy;
		node->sphere.center.z = cz;
		node->sphere.radius = rad;
		node->color.R = R;
		node->color.G = G;
		node->color.B = B;
		node->next = *list;
		
		*list = node;
	}
}

int intersect_sphere(ray_t ray, sphere_t sphere, double *t){
	//Quadratic Variables
	double A;
	double B;
	double C;
	//Distance variables
	double t0;
	double t1;
	
	ray.dir = normalize(ray.dir);
	

	A = 1;
	
	B = 2 * (ray.dir.x*(ray.orig.x-sphere.center.x) + 
			 ray.dir.y*(ray.orig.y-sphere.center.y) + 
		 	 ray.dir.z*(ray.orig.z-sphere.center.z));
	
	C = (ray.orig.x - sphere.center.x)*(ray.orig.x - sphere.center.x) + 
		(ray.orig.y - sphere.center.y)*(ray.orig.y - sphere.center.y) +
		(ray.orig.z - sphere.center.z)*(ray.orig.z - sphere.center.z) - sphere.radius*sphere.radius;
	
	//If the discrimant is 0 we get a complex #, we don't want that
	if ((B*B - 4*A*C) < 0){
		return 0;
	}

	//Checks both the + and - options for the quadratic
	t0 = (-B + sqrt(B*B - 4*A*C)) / (2*A);
	t1 = (-B - sqrt(B*B - 4*A*C)) / (2*A);

	//Sphere is behind the origin
	if (t0 < 0 && t1 < 0){	
		return 0;
	}

	//Else we just want the shorter distance
	else if (t0 < t1){
		*t = t0;
	}

	else if (t1 < t0){
		*t = t1;
	}
	
	return 1;
}

color_t cast(ray_t ray, obj_t *list){
	obj_t *curr; // current object
	double t;
	double min_t = 1000.0; // just a random high # so that we are below on first loop
	color_t color;
	color.R = 1;
	color.G = 1;
	color.B = 1;
	//If the ray intersects the sphere given by the object and t is less than the minimum we set the color and min_t
	for (curr = list; curr != NULL; curr = curr->next){
		if (intersect_sphere(ray, curr->sphere, &t)){
			if (t < min_t){
				min_t = t;
				color = curr->color;
			}
		}
	}
	return color;
}

void main(){
	//initilization
	sphere_t sphere;
	ray_t ray;
	obj_t *list;
	color_t color;
	int x;
	int y;
	double t;
	
	//reads file
	read_objs(&list);
	
	//PPM initialization line
	printf("P6\n1000 1000\n255\n");
	
	//Iterates through each pixel and writes the color we want into it
	for(y = 0; y < 1000; y++){
		for(x = 0; x < 1000; x++){
			ray.orig.x = 0;
			ray.orig.y = 0;
			ray.orig.z = 0;
			ray.dir.x = (-0.5 + x/1000.0);
			ray.dir.y = (0.5 - y/1000.0);
			ray.dir.z = 1;
			
			ray.dir = normalize(ray.dir);
			
			color = cast(ray, list);
			
			printf("%c%c%c", (unsigned char)(color.R * 255), (unsigned char)(color.G * 255), (unsigned char)(color.B * 255));
		}
	}
	
}

