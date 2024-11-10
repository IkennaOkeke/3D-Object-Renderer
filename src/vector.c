#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>


typedef struct {
    float x;
    float y;
    float z;
} Vec3;



Vec3 add(Vec3 v1, Vec3 v2) {

    Vec3 v3 = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return v3;

}



Vec3 subtract(Vec3 v1, Vec3 v2) {

    Vec3 v3 = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return v3;

}



Vec3 scalarMultiply(float s, Vec3 v) {

    Vec3 v3 = {s * v.x, s * v.y, s * v.z};
    return v3;

}



Vec3 scalarDivide(Vec3 v, float d) {

    Vec3 v3 = {v.x / d, v.y / d, v.z / d};
    return v3;

}



Vec3 normalize(Vec3 v) {

    Vec3 u = scalarDivide(v, length(v));
    return u;

}



float dot(Vec3 v1, Vec3 v2) {

    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);

}



float length2(Vec3 v) {

    return (v.x * v.x + v.y * v.y + v.z * v.z);

}



float length(Vec3 v) {

    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

}



float distance2(Vec3 v1, Vec3 v2) {

    return length2(subtract(v1, v2));

}



float distance(Vec3 v1, Vec3 v2) {

    return length(subtract(v1, v2));

}



#endif