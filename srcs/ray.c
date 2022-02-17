#include "structs.h"

/* Ray Constructor */

t_ray   ray(t_point3 orig, t_vec3 dir)
{
    t_ray   ray;

    ray.orig = orig;
    ray.dir = dir;

    return (ray);
}

/* 
     P(t) = Origin + t * Direction
    A point away from the ray origin in the direction vec ray dir * t
*/

t_point3    ray_at(t_ray *ray, double t)
{
    t_point3    at;

    at = vadd(ray->orig, vmult_(ray->dir, t));
    return (at);
}

// Primary_ray Constructor 

t_ray   ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;

    ray.orig = cam->orig;
    // Unit vector in ray dir 
    // left_bottom + u * horizontal + v * vertical - origin 
    ray.dir = vunit(vminus(vadd(vadd(cam->lower_left_bottom, vmult_(cam->horizontal, u)), vmult_(cam->vertical, v)),
                                cam->orig));
    return (ray);
}


t_hit_record    record_init(void)
{
    t_hit_record    record;

    record.tmin = EPSILON;
    record.tmax = INFINITY;
    return (record);
}


// Return the color value of the pixel that the ray finally got
//      Applying the hit record struct here 

t_color3    ray_color(t_scene *scene)
{
    double          t;
    t_vec3          n;

    // if the ray hits the sphere (if the ray and the sphere have an intersection, and the intersection is in front of the camera)
    scene->rec = record_init();
    if (hit(scene->world, &scene->ray, &scene->rec))
        return (phong_lighting(scene));
    else 
    {
        t = 0.5 * (scene->ray.dir.y + 1.0);
        // (1 - t) * white + t * light blue
        return (vadd(vmult_(color3(1, 1, 1), 1.0 - t), vmult_(color3(0.5, 0.7, 1.0), t)));
    }
}