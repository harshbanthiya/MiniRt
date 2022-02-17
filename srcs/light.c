#include "structs.h"

/* Light Source Constructor */

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

*/

t_color3    point_light_get(t_scene *scene, t_light *light)
{
    t_color3    diffuse;
    t_vec3      light_dir;
    double      kd; // diffuse intensity

    light_dir = vunit(vminus(light->origin, scene->rec.p));
    // A vector from the intersection to the light source (normalised)
    // Cos (theta) is 0 when the theta value is 90 degrees and becomes negative when theta is an obtuse angle
    // Meaning perpendicular to light source is max brightness and parallel to light source lowest brightness 
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
    //  The above line is the dot product of (the vector starting at the intersection towards the light source)
    //  and ( the normal vector at the intersection)
    diffuse = vmult_(light->light_color, kd);
    return (diffuse);
}