#include "structs.h"

vec3    *make_vec3(double x, double y, double z)
{
    vec3   *new;
    new =  (vec3 *)malloc(sizeof(vec3));

    new->x = x;
    new->y = y;
    new->z = z;

    return (new);
}