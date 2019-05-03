#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "camera.h"
#include "material.h"

using namespace std;


// Point of this function is to approximate a randomized reflection from
//The hit site. To do this, directions can be approximated by creating a
//"hit" sphere at the hit site, and approximating a direction from the hit point to inside the sphere



vec3 color(const ray& r, hitable *world, int depth) {
	// Creates "linear interpolation aka lerp
	// Given center sphere 0,0,-1 and hit r
	hit_record rec;

	if (world->hit(r, 0.001, FLT_MAX, rec)) {

		ray scattered;
		vec3 attenuation;

		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation*color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}


		
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5* (unit_direction.y() + 1.0);
		return (1.0 - t)* vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
	



}


int main() {
	int nx = 200;
	int ny = 100;
	int ns = 100;
	
	hitable *list[4];
	float R = cos(M_PI / 4);
	//list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0.8, 0.3, 0.3)));
	//// this sphere is the ground lolol
	//list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(0.8, 0.8, 0.0)));


	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1,0.2,0.5)));
	
	// this sphere is the ground lolol
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8,0.8,0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 1.0));

	camera cam(vec3(-2,2,1), vec3(0,0,0), vec3(0,1,0), 90, float(nx)/float(ny));
	hitable *world = new hitable_list(list, 4);

	ofstream myFile;
	myFile.open("test.ppm");
	
	myFile << "P3\n" << nx << " " << ny << "\n255\n";

	for (int j = ny-1; j > 0; j--) {
		cout << j <<endl;
		for (int i = 0; i < nx; i++){

			vec3 col(0, 0, 0);

			for (int s = 0; s < ns; s++) {
				float u = float(i + (rand() / (RAND_MAX + 1.0))) / float(nx);
				float v = float(j + (rand() / (RAND_MAX + 1.0))) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world,0);
			}
			
			// ray from 0,0,0 to wherever then color

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int( col[0] * 255.99);
			int ig = int( col[1] * 255.99);
			int ib = int( col[2] * 255.99);
			myFile << ir << " " << ig << " " << ib << "\n";

			}
	}


	//cout << ir << " " << ig << " " << ib << "\n";
	//myFile << ir << " " << ig << " " << ib << "\n";
		
	
	myFile.close();
}