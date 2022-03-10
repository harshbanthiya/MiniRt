#ifndef RAY_H
# define RAY_H

#include "structs.h"
#include "vector.h"

static inline void ray_sphere(const t_vec3 *orig, const t_vec3 *ray,
        const t_sphere *sphere, t_hit_record *hit)
{
    const t_vec3 oc = sub(*orig, sphere->center);
    const float a = dot(*ray, *ray);
    const float b = dot(oc, *ray);
    const float c = dot(oc, oc) - sphere->radius * sphere->radius;  
    const float d = b * b - a * c;

    if (d <= EPSILON)
        return ((void)(hit->dist = -1));
    hit->dist = (-b - sqrt(b * b - a * c)) / a;
    hit->p = add(*orig, mult(*ray, hit->dist));
    hit->normal = normalize(sub(hit->p, sphere->center));
}

static inline void  ray_plane(const t_vec3 *orig, const t_vec3 *ray,
        const t_plane *plane, t_hit_record *hit)
{
    const float d = dot(plane->normal, *ray);
    
    if (d >= EPSILON && d <= EPSILON)
        return ((void)(hit->dist = -1));
    hit->dist = dot(sub(plane->pos, *orig), plane->normal) / d;
    hit->p = add(*orig, mult(*ray, hit->dist));
    hit->normal = plane->normal;
}

static inline int ray_scene(const t_vec3 *orig, const t_vec3 *ray,
        const t_scene *scene, t_hit_record *closest)
{
    t_hit_record        hit;
    register t_object   *obj;

    obj = (t_object *)scene->world;
    closest->dist = -1;
    while (obj->func)
    {
        hit.dist = -1;
        obj->func(orig, ray, (void *)&obj->ptr, &hit);
        if (hit.dist > CAMERA_CLIP_START 
            && (closest->dist == -1 || hit.dist < closest->dist))
        {
            closest->dist = hit.dist;
            closest->p = hit.p;
            closest->normal = hit.normal;
            closest->obj = obj;
        }
        obj++;
    }
    return (closest->dist != -1); 
}

#endif 