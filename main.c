/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:19:26 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/02/22 16:12:30 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include "includes/minirt.h"

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


int main(int argc, char **argv)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    t_scene scene;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1280, 720, "test");
    img.img = mlx_new_image(mlx, 1280, 720);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    /*Argument checking*/
    if (argc != 2)
    {
        printf("Usage: ./minirt <path/to/file.rt>\n");
        mlx_destroy_image(mlx, img.img);
        return 1;
    }
    //open file, parse it and put stuff somewhere
    scene.fd = open_file(argv[1]);
    parse_scene(&scene);
    /* Gradient */

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
            color = r << 16 | g << 8 | b;
            my_mlx_put_pixel(&img, ii, 720 - jj, color);
            g = jj / 720 * 256; // Converting to int and multiply by 255.999 because decimal is discarded hence getting the gradient
        }
        r = ii / 1280 * 256;
    }

    /* Circle */
 
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