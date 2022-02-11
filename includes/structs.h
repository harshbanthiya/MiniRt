#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct vector3
{
    double x;
    double y;
    double z;
};

typedef struct vector3 vec3;
typedef struct vector3 point;
typedef struct vector3 color;

typedef struct
{
    vec3    *position;
    vec3    *direction;
    double  canvasposition;
}camera;

typedef struct
{
    vec3    *color;
    vec3    *position;
    float   radius;
}sphere;

typedef struct
{
    vec3    *position;
}light;

typedef struct
{
    double  diffuse;
    double  ambience;
    double  specularity;
    double  specular;
}material;

vec3    *make_vec3(double x, double y, double z);
