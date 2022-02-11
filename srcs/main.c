#include "structs.h"

typedef struct s_data
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

void    my_mlx_put_pixel(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}


void setupscene(camera *c, light *l, sphere *sp, material *m)
{
    c->position = make_vec3(0., 0.0, 3.5);
    c->direction = make_vec3(0., 0., -1.);
    c->canvasposition = 2.8;

    l->position = make_vec3(0., -1, -0.78);

    sp->position = make_vec3(0., 0., 2.6);
    sp->radius = 0.3;
    sp->color = make_vec3(0.9, 0.2, 0.1);

    m->ambience = 0.2;
    m->diffuse = 0.7;
    m->specularity = 50;
    m->specular = 0.9;
}

int main ()
{
    camera cam;
    light  l;
    sphere sp;
    material mat;
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1280, 720, "test");
    img.img = mlx_new_image(mlx, 1280, 720);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    setupscene(&cam, &l, &sp, &mat);
    
    int r = 0;
    int b = 0;
    int color = 0;
    double ii = -1;
    while (++ii < 1280)
    {
        double jj = 720;
        int g = 0;
        while (--jj > 0)
        {
            color = r | g | b;
            my_mlx_put_pixel(&img, ii, 720 - jj, color);
            g = jj / 256;
        }
        r = ii / 1280 * 256;
    }
    
    int radius = 200;
    int i = -201;
    int point;

    while (++i < 200)
    {
        int j = -201;
        while (++j < 200)
        {
            point = pow(i, 2) + pow(j, 2);
            if (sqrt(point) <= radius)
                my_mlx_put_pixel(&img, i + 620, j + 350, 0x00FF0000);
        }
    }


    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
 
    return (0);
}