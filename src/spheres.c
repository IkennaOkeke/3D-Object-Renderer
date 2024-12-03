#include <stdlib.h>
#include "spheres.h"
#include "vector.h"
#include "math.h"



// world initialization function
void worldInit(World *world) {

    // allocates enough size in sphere array for one sphere, sets capacity to 1, and sets size to 0 
    world->spheres = (Sphere **)malloc(sizeof(Sphere*));
    world->capacity = 1;
    world->size = 0;

}



// frees world memory
void freeWorld(World *world) {

    for (int sphere_index = 0; sphere_index < world->size; sphere_index++) {

        free((world->spheres)[sphere_index]);

    }

    free(world->spheres);

}



// add sphere function
void addSphere(World *world, Sphere *sphere) {

    // if the capacity has been reached, doubles it using realloc and changes capacity variable accordingly
    if (world->capacity == world->size) {
        world->spheres = (Sphere **)realloc(world->spheres, 2 * (world->capacity) * sizeof(Sphere*));
        world->capacity *= 2;
    }

    // adds sphere to sphere array, and adjust world size variable accordingly
    *(world->spheres + world->size) = sphere;
    world->size += 1;

}



// create sphere function
Sphere *createSphere(float radius, Vec3 position, Vec3 color) {

    // creates and allocates space for the sphere
    Sphere *new_sphere = (Sphere *)malloc(sizeof(Sphere));

    // sets the spheres radius, position, and colour accordingly
    new_sphere->r = radius;
    new_sphere->pos = position;
    new_sphere->color = color;
    
    // returns the sphere (pointer)
    return new_sphere;

}   


// doesIntersect function
int doesIntersect(const Sphere *sphere, Vec3 rayPos, Vec3 rayDir, float *t) {

    // calculates a, b, and c values of quadatric formula
    Vec3 temp = subtract(rayPos, sphere->pos);
    float a = dot(rayDir, rayDir);
    float b = 2 * dot(rayDir, temp);
    float c = dot(temp, temp) - ((sphere->r) * (sphere->r));

    // calculates discriminant
    float discriminant = (b * b) - (4 * a * c);

    // non real number if discriminant is negative, meaning no intersection
    if (discriminant < 0) {
        return 0;
    }

    float sqrt_discriminant = sqrt(discriminant);

    // solves '+' version of quadratic formula
    float t_plus = ((-b) + sqrt_discriminant) / (2 * a);
    // only one solution if the discriminant is zero, return 0 to signify sphere behind camera, return 1 to signify sphere in view of camera and updated t value
    if (discriminant == 0) {
        
        if (t_plus < 0) {
            return 0;
        }

        *t = t_plus;; 
        return 1;
    }


    float t_minus = ((-b) - sqrt_discriminant) / (2 * a);
    // two solutions if we have reached this far, return 0 to signify sphere behind camera
    if ((t_minus < 0) && (t_plus < 0)) {
        return 0;
    }

    // sphere is in view of camera, we return 1 and update t based on smallest solution (this t value is the front of the sphere)
    if ((t_plus > t_minus) && (t_minus >= 0)) {
        *t = t_minus;
        return 1;
    }
    else if ((t_minus > t_plus) && (t_plus >= 0)) {
        *t = t_plus;
        return 1;
    }

    // returns 0 if needed
    return 0;
}
