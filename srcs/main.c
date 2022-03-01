#include "structs.h"

/* To see the gradient in this, run make, then ./minirt > rgb.ppm and then open rgb.ppm */

void    write_color(t_color3 pixel_color)
{
    printf("%d %d %d\n", (int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z));
}

t_scene     *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka;

    if (!(scene = (t_scene *) malloc (sizeof (t_scene))))
        return (NULL);
    scene->canvas = canvas(1200, 800);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0));
    world = object(SP, sphere(point3 (-2, 0, -5), 2), color3(0.5, 0, 0));
    objadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
    objadd(&world, object(SP, sphere(point3(0, -1000, 0), 990), color3(1, 1, 1)));
    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
    scene->light = lights;
    ka = 0.1;
    scene->ambient = vmult_(color3(1, 1, 1), ka);
    scene->obj_count = 0;
    return (scene);
}   

int main ()
{
    int         i;
    int         j;
    double      u;
    double      v;
    t_color3    pixel_color;
    t_scene     *scene;

    scene = scene_init();
    printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height); // PPM format canvas width and height
    j = scene->canvas.height;
    while (--j >= 0)
    {
        i = -1;
        while (++i < scene->canvas.width)
        {
            u = (double) i / (scene->canvas.width - 1); 
            v = (double) j / (scene->canvas.height - 1);
            scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
            write_color(pixel_color);
        }
    }
    return (0);
}