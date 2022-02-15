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

typedef struct vector3 t_vec3;
typedef struct vector3 t_point3;
typedef struct vector3 t_color3;

// All the vectors below are just to give you an idea and not finalised and I will change them as I will need stuff in it  
typedef struct
{
    t_vec3    *position;
    t_vec3    *direction;
    double  canvasposition;
}camera;

typedef struct
{
    t_vec3    *color;
    t_vec3    *position;
    float   radius;
}sphere;

typedef struct
{
    t_vec3    *position;
}light;

typedef struct
{
    double  diffuse;
    double  ambience;
    double  specularity;
    double  specular;
}material;

t_vec3 vec3(double x, double y, double z);
t_point3 point3(double x, double y, double z);
t_point3 color3(double r, double g, double b);
void    vset(t_vec3 *vec, double x, double y, double z);
double vlength2(t_vec3 vec);
double  vlength(t_vec3 vec);
t_vec3  vadd(t_vec3 v1, t_vec3 v2);
t_vec3 vadd_(t_vec3 vec, double x, double y, double z);
t_vec3  vminus(t_vec3 v1, t_vec3 v2);
t_vec3 vminus_(t_vec3 vec, double x, double y, double z);
t_vec3 vmult(t_vec3 v1, t_vec3 v2);
t_vec3 vmult_(t_vec3 v, double n);
t_vec3 vdivide(t_vec3 v, double n);
double vdot(t_vec3 v1, t_vec3 v2);
t_vec3 vcross(t_vec3 v1, t_vec3 v2);
t_vec3 vunit(t_vec3 v);
t_vec3 vmin(t_vec3 vec1, t_vec3 vec2);
