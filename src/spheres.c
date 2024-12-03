#include "spheres.h"
#include "vector.h"



typedef struct {
    float r;
    Vec3 pos;
    Vec3 color;
} Sphere;



typedef struct {
    Sphere **spheres;
    int size;
    int capacity;
} World;



void worldInit(World *world) {

    world->spheres = (Sphere **)malloc(sizeof(Sphere*));
    world->capacity = 1;

}



void freeWorld(World *world) {

    free(world->spheres);

}



void addSphere(World *world, Sphere *sphere) {

    if (world->capacity == world->size) {
        world->spheres = (Sphere **)realloc(world, 2 * (world->capacity) * sizeof(Sphere*));
        world->capacity *= 2;
    }

    *(world->spheres + world->size) = sphere;
    world->size += 1;

}



Sphere *createSphere(float radius, Vec3 position, Vec3 color) {
    Sphere *new_sphere = (Sphere *)malloc(sizeof(Sphere));
    new_sphere->r = radius;
    new_sphere->pos = position;
    new_sphere->color = color;
    return new_sphere;
}   



int doesIntersect(const Sphere *sphere, Vec3 rayPos, Vec3 rayDir, float *t);
