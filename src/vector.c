// includes math library for sqrt calculations
#include <math.h>



// vector structure
typedef struct {
    float x;
    float y;
    float z;
} Vec3;



// vector addition calculation
Vec3 add(Vec3 v1, Vec3 v2) {

    return (Vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};

}



// vector subtraction calculation
Vec3 subtract(Vec3 v1, Vec3 v2) {

    return (Vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};

}



// scalar multiplication calculation
Vec3 scalarMultiply(float s, Vec3 v) {

    return (Vec3){s * v.x, s * v.y, s * v.z};

}


// scalar division calculation
Vec3 scalarDivide(Vec3 v, float d) {

    return (Vec3){v.x / d, v.y / d, v.z / d};

}



// vector normalization calculation
Vec3 normalize(Vec3 v) {

    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (Vec3){v.x / length, v.y / length, v.z / length};

}



// dot product calculation
float dot(Vec3 v1, Vec3 v2) {

    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);

}



// length squared calculation
float length2(Vec3 v) {

    return (v.x * v.x + v.y * v.y + v.z * v.z);

}



// length calculation
float length(Vec3 v) {

    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

}



// distance squared calculation
float distance2(Vec3 v1, Vec3 v2) {

    return length2(subtract(v1, v2));

}



// distance calculation
float distance(Vec3 v1, Vec3 v2) {

    return length(subtract(v1, v2));

}
