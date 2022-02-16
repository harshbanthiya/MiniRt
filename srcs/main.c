#include "structs.h"

/* To see the gradient in this, run make, then ./minirt > rgb.ppm and then open rgb.ppm */

void    write_color(t_color3 pixel_color)
{
    printf("%d %d %d\n", (int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z));
}

int main ()
{
    int         i;
    int         j;
    double      u;
    double      v;
    t_color3    pixel_color;
    t_canvas    canv;
    t_camera    cam;
    t_ray       ray;
    t_object    *world;


    canv = canvas(1200, 800);
    cam = camera(&canv, point3(0, 0, 0));
    world = object(SP, sphere(point3(-2, 0, -5), 2));
    objadd(&world, object(SP, sphere(point3(2, 0, -5), 2)));
    objadd(&world, object(SP, sphere(point3(0, -1000, 0), 990)));
    printf("P3\n%d %d\n255\n", canv.width, canv.height); // PPM format canvas width and height
    j = canv.height;
    while (--j >= 0)
    {
        i = -1;
        while (++i < canv.width)
        {
            u = (double) i / (canv.width - 1); 
            v = (double) j / (canv.height - 1);
            ray = ray_primary(&cam, u, v);
            pixel_color = ray_color(&ray, world);
            write_color(pixel_color);
        }
    }
    return (0);
}