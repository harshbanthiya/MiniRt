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

// Return the color value of the pixel that the ray finally got

t_color3    ray_color(t_ray *r, t_sphere *sphere)
{
    double  t;
    t_vec3  n;
    
    t = hit_sphere(sphere, r);
    if (t > 0.0)
    {
        // normalised version of the normal sphere vector
        n = vunit(vminus (ray_at(r, t), sphere->center));
        return (vmult_(color3 (n.x + 1, n.y + 1, n.z + 1), 0.5));
    }
    t = 0.5 * (r->dir.y + 1.0);
    // (1 - t) * white + t * light blue
    return (vadd(vmult_(color3(1, 1, 1), 1.0 - t), vmult_(color3(0.5, 0.7, 1.0), t)));
}