/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:23:21 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/02/24 13:29:12 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

# define PI                 3.14159265358979323846264338327950288
# define TWO_PI             6.28318530717958647692528676655900577
# define PI_TWO             1.57079632679489661923132169163975144
# define EPSILON            0.0001

# define WIDTH              480
# define HEIGHT             480

# define KEY_A	            0
# define KEY_S		        1
# define KEY_D		        2
# define KEY_W		        13

# define KEY_ESCAPE			53
# define KEY_SPACE			49
# define KEY_LSHIFT			257
# define KEY_LEFT			123
# define KEY_UP				126
# define KEY_RIGHT			124
# define KEY_DOWN			125

#define LUMEN 3

typedef struct vector3 t_vec3;
typedef struct vector3 t_point3;
typedef struct vector3 t_color3;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_sphere t_sphere;
typedef struct s_hit_record t_hit_record;
typedef struct s_object t_object;
typedef struct s_light t_light;
typedef struct s_scene t_scene;
typedef struct s_ambient t_ambient;
typedef struct s_plane  t_plane;

struct vector3
{
    float   x;
    float   y;
    float   z;
};

struct s_camera
{
    t_point3    pos; // Camera origin or position of the camera
    t_point3    rot; // Camera Rotation 
    int         width; // viewport height
    int         height; // viewport width;
    float       fov_pixel; // Field of view pixel info
    int         set;
};

struct s_canvas
{
    int     width; // canvas width
    int     height; // canvas height 
    void    *ptr;   // mlx 
    void    *win;
    void    *img;
    int     *buf;
};

struct s_sphere
{
    t_point3    center;
    float       radius; 
};

struct s_plane
{
    t_point3    pos;
    t_vec3      normal;      
};

struct s_hit_record
{
    t_point3    p; // coordinate of intersection
    t_vec3      normal; // normal vector at the intersection
    float       dist;
    t_object    *obj;
};

struct  s_object
{
    void            (*func)();
    union 
    {
        int         ptr;
        t_sphere    sphere;
        t_plane     plane;
    };
    float           ka;
    float           kd;
    float           ks;
    float           specularity;
    int             color; 
};

struct s_light
{
    t_point3    position; // Position of light
    int         color;    
    float       intensity;
    int         set;
};

struct  s_ambient
{
    float       intensity;
    int         color;
    int         set;
};

struct s_scene            // Making a new master struct to keep a list of lights and objects 
{
    t_canvas        canvas;
    t_camera        camera;
    int             cam_count; 
    t_object        world[1024];  // List of objects
    int             obj_count;
    t_object        light[64];  // List of light sources 
    int             light_count;
    //t_color3        ambient;
    t_ambient       ambient;
    int             ambient_count;
    int             keys[1024];
    int             fd;
};



/*
// Utils 
t_vec3      vec3(double x, double y, double z);
t_point3    point3(double x, double y, double z);
t_point3    color3(double r, double g, double b);
void        vset(t_vec3 *vec, double x, double y, double z);
double      vlength2(t_vec3 vec);
double      vlength(t_vec3 vec);
t_vec3      vadd(t_vec3 v1, t_vec3 v2);
t_vec3      vadd_(t_vec3 vec, double x, double y, double z);
t_vec3      vminus(t_vec3 v1, t_vec3 v2);
t_vec3      vminus_(t_vec3 vec, double x, double y, double z);
t_vec3      vmult(t_vec3 v1, t_vec3 v2);
t_vec3      vmult_(t_vec3 v, double n);
t_vec3      vdivide(t_vec3 v, double n);
double      vdot(t_vec3 v1, t_vec3 v2);
t_vec3      vcross(t_vec3 v1, t_vec3 v2);
t_vec3      vunit(t_vec3 v);
t_vec3      vmin(t_vec3 vec1, t_vec3 vec2);
t_object    *olast(t_object *list);
void        objadd(t_object **list, t_object *new);

// Ray 
t_ray           ray(t_point3 orig, t_vec3 dir);
t_point3        ray_at(t_ray *ray, double t);
t_color3        ray_color(t_scene *scene);
t_ray           ray_primary(t_camera *cam, double u, double v);
t_hit_record    record_init(void);

// Scene
t_camera    camera(t_canvas *canvas, t_point3 orig);
t_canvas    canvas(int width, int height);
t_sphere    *sphere(t_point3 center, double radius);
t_object    *object(t_object_type type, void *element, t_color3 albedo);

// Intersect
void        set_face_normal(t_ray *r, t_hit_record *rec);
bool        hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
bool        hit(t_object *world, t_ray *ray, t_hit_record *rec);
bool        hit_obj(t_object *world, t_ray *ray, t_hit_record *rec);

// light 
t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio);
t_color3    phong_lighting(t_scene *scene);
t_color3    point_light_get(t_scene *scene, t_light *light);
t_vec3      reflect(t_vec3 v, t_vec3 n);
bool        in_shadow(t_object *objs, t_ray light_ray, double light_len);
*/

#endif