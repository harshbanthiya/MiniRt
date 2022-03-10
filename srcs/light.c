#include "structs.h"

/* Light Source Constructor */
/*
t_light *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
    t_light     *light;

    if (!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->origin = light_origin;
    light->light_color = light_color;
    light->bright_ratio = bright_ratio;

    return (light);
} 
*/
/* 
    The Phong Lighting Model

    Ambient - (Ambient / Environment Light) : It is an element that simplifies the light reflected from other objects 
                                              and the scattered light in the atmosphere. Factors that affect the overal brightness
                                              of the scene.

    Diffuse (Scattered light / Diffuse reflected light)
                                            : It is a simplified element of light reaching our eyes through diffuse reflection

    Specular (Reflected light / Specularly bright reflected light)
                                            : This is the element that simplifies the light reaching our eyes through specular
                                              reflection

    Phong lighting model is the sum total of all the three lighting systems
*/ 

/* 
    In order to calculate the amount of light reaching the intersection, we need to calculate 
    the sum of specular and diffuse for all light sources in the scene and add the ambient to it. 

    Post that, the final pixel color is obtained by multiplying the total amount of light by the 
    reflectance of the object. 
*/

t_color3    phong_lighting(t_scene *scene)
{
    t_color3    light_color;
    t_object    *lights;

    light_color = color3(0, 0, 0); // If there is no light source, the amount of light should be (0, 0, 0)
    lights = scene->light;
    while(lights) // We need to find both diffuse and specular values for all lights from multiple light sources
    {   
        if (lights->type == LIGHT_POINT)
            light_color = vadd(light_color, point_light_get(scene, lights->element));
            lights = lights->next;
    }
    light_color = vadd(light_color, scene->ambient);
    // After getting the amount of light by all the light sources, mutiply by reflectances of objs
    // if the value of light color is greater than (1, 1 , 1) return (1, 1, 1)
    return (vmin (vmult(light_color, scene->rec.albedo), color3 (1, 1, 1)));
}

/* 
    Now comes the tricky lighting implementation 
    Diffuse and Specular 
    The angle between two vectors can be found by the dot product 
     // A vector from the intersection to the light source (normalised)
    // Cos (theta) is 0 when the theta value is 90 degrees and becomes negative when theta is an obtuse angle
    // Meaning perpendicular to light source is max brightness and parallel to light source lowest brightness 
    //  The above line is the dot product of (the vector starting at the intersection towards the light source)
    //  and ( the normal vector at the intersection)
*/

t_color3    point_light_get(t_scene *scene, t_light *light)
{
    t_color3    diffuse;
    t_color3    ambient;
    t_vec3      light_dir;
    double      kd; // diffuse intensity
    t_color3    specular;
    t_vec3      view_dir;
    t_vec3      reflect_dir;
    double      spec;
    double      ksn;
    double      ks;
    double      ka;
    double      brightness;
    double      light_len;
    t_ray       light_ray;

    light_dir = vminus(light->origin, scene->rec.p);
    light_len = vlength(light_dir);
    light_ray = ray(vadd(scene->rec.p, vmult_(scene->rec.normal, EPSILON)), light_dir);
    if (in_shadow(scene->world, light_ray, light_len))
        return (color3(0, 0, 0));
    light_dir = vunit(light_dir);
    view_dir = vunit(vmult_(scene->ray.dir, -1));
    reflect_dir = reflect(vmult_(light_dir, -1), scene->rec.normal);
    ka = 0.1; // ambient strength
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
    ksn = 69; // specularity value (nice!)
    ks = 0.5; // specularity strength;
    diffuse = vmult_(light->light_color, kd);
    ambient = vmult_(light->light_color, ka);
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
    specular = vmult_(vmult_(light->light_color, ks), spec);
    brightness = light->bright_ratio * LUMEN;
    return (vmult_(vadd(vadd(ambient, diffuse), specular), brightness));
}


/* 
    Specular Lighting 
    The value of specular is a cosine value according to the size of the angle between the view_direction 
    and reflection_direction 
    which is the vector from the intersection point to the camera origin and light_direction, symmetrically 
    based on the normal(). Specularity value (ksn) 

    In short, when the view_direction and reflection_direction completely match (The angle between them is 0 degrees)
    the amount of light reaching the camera through specular reflection will be the largest. and decreasing as the angle 
    between them increases 

    Just like diffuse the value is obtained using the Dot Product of two vectors (view_dir, reflect_dir)

    specular = spec ^ ksn 
*/

/* Now we need a function to to get the reflected light vector */

t_vec3  reflect(t_vec3 v, t_vec3 n)
{
    // v - 2 * dot(v, n) * n
    return (vminus (v, vmult_(n, vdot(v, n) * 2)));
}

/* 
    Shadows need to be implemented, it is pretty basic, if there is an object between the hit point
    and light source, it will apply the shadow
    We will shoot a ray from hit point to light_source 
    Tmax is light len which is the distance from hit point to origin of light source
    This is because shadows can appear even when there are other objects behind the light source
*/

bool    in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
    t_hit_record    rec;

    rec.tmin = 0;
    rec.tmax = light_len;
    if (hit(objs, &light_ray, &rec))
        return (true);
    return (false);
}