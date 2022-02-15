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
    double      r;
    double      g;
    double      b;
    t_color3    pixel_color;
    int         canvas_width;
    int         canvas_height;

    canvas_width = 1200;
    canvas_height = 900;
    printf("P3\n%d %d\n255\n", canvas_width, canvas_height); // PPM format canvas width and height
    j = canvas_height;
    while (--j >= 0)
    {
        i = -1;
        while (++i < canvas_width)
        {
            pixel_color.x = (double) i / (canvas_width - 1); 
            pixel_color.y = (double) j / (canvas_height - 1);
            pixel_color.z = 0.25;
            write_color(pixel_color);
        }
    }
    return (0);
}