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
static inline void	ray_cylinder(const t_vec3 *orig, const t_vec3 *ray,
		const t_cylinder *cylinder, t_hit_record *hit)
{
	const t_vec3	oc = sub(*orig, cylinder->pos);
	const float	card = dot(cylinder->ca, *ray);
	const float caoc = dot(cylinder->ca, oc);
    const float a = cylinder->caca - card * card;
	const float	b = cylinder->caca * dot(oc, *ray) - caoc * card;
    const float h = b * b - a * (cylinder->caca * dot2(oc) - caoc * caoc 
		- cylinder->rad * cylinder->rad * cylinder->caca), y;
	if (h < 0.0)
		return ((void)(hit->dist = -1));
	*(float *)&h = sqrtf(h);
	hit->dist = (-b - h) / a;
	*(float *)&y = caoc + hit->dist * card;
	if (y > 0.0 && y < cylinder->caca)
		hit->normal = normalize(mult(add(oc, sub(mult(*ray, hit->dist), mult(\
mult(cylinder->ca, y), 1.0 / cylinder->caca))), 1.0 / cylinder->rad));
	else
	{
		hit->dist = (cylinder->caca * !(y < 0.0) - caoc) / card;
		if (fabs(b + a * hit->dist) >= h)
			return ((void)(hit->dist = -1));
		hit->normal = normalize(mult(mult(cylinder->ca, sign(y)), \
			1.0 / cylinder->caca));
	}
	hit->p = add(*orig, mult(*ray, hit->dist));
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