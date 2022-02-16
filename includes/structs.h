/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:23:21 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/02/15 19:23:22 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct vector3
{
    double x;
    double y;
    double z;
};

typedef struct vector3 t_vec3;
typedef struct vector3 t_point3;
typedef struct vector3 t_color3;

struct s_ray
{
    t_point3    orig;
    t_vec3      dir;
};

typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;

struct s_camera
{
    t_point3    orig; // Camera origin or position of the camera
    double      viewport_h; // viewport height
    double      viewport_w; // viewport width;
    t_vec3      horizontal; // horizontal length vector;
    t_vec3      vertical; // vertical length vector;
    double      focal_len; // focal length
    t_point3    lower_left_bottom; // lower left corner;
};

struct s_canvas
{
    int     width; // canvas width
    int     height; // canvas height 
    double  aspect_ratio; // aspect ratio;
};


// All the vectors below are just to give you an idea and not finalised and I will change them as I will need stuff in it  

typedef struct
{
    t_vec3    *color;
    t_vec3    *position;
    float   radius;
}sphere;

typedef struct
{
    t_vec3    *position;
}light;

typedef struct
{
    double  diffuse;
    double  ambience;
    double  specularity;
    double  specular;
}material;

t_vec3 vec3(double x, double y, double z);
t_point3 point3(double x, double y, double z);
t_point3 color3(double r, double g, double b);
void    vset(t_vec3 *vec, double x, double y, double z);
double vlength2(t_vec3 vec);
double  vlength(t_vec3 vec);
t_vec3  vadd(t_vec3 v1, t_vec3 v2);
t_vec3 vadd_(t_vec3 vec, double x, double y, double z);
t_vec3  vminus(t_vec3 v1, t_vec3 v2);
t_vec3 vminus_(t_vec3 vec, double x, double y, double z);
t_vec3 vmult(t_vec3 v1, t_vec3 v2);
t_vec3 vmult_(t_vec3 v, double n);
t_vec3 vdivide(t_vec3 v, double n);
double vdot(t_vec3 v1, t_vec3 v2);
t_vec3 vcross(t_vec3 v1, t_vec3 v2);
t_vec3 vunit(t_vec3 v);
t_vec3 vmin(t_vec3 vec1, t_vec3 vec2);

// Ray 
t_ray   ray(t_point3 orig, t_vec3 dir);
t_point3    ray_at(t_ray *ray, double t);
t_color3    ray_color(t_ray *r);
t_ray   ray_primary(t_camera *cam, double u, double v);

// Scene
t_camera    camera(t_canvas *canvas, t_point3 orig);
t_canvas    canvas(int width, int height);

