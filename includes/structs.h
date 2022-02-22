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

#ifndef STRUCTS_H
# define STRUCTS_H
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SP 0
#define LIGHT_POINT 1
#define EPSILON 1e-6 // 0.000001
#define LUMEN 3

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
typedef struct s_sphere t_sphere;
typedef struct s_hit_record t_hit_record;
typedef struct s_object t_object;
typedef int    t_object_type;

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

struct s_sphere
{
    t_point3    center;
    double      radius;
    double      radius2; // since r square is used alot 
};

struct s_hit_record
{
    t_point3    p; // coordinate of intersection
    t_vec3      normal; // normal vector at the intersection
    double      tmin;
    double      tmax;
    double      t;      // t is the distance between origin of the ray and the intersection
    bool        front_face; 
    t_color3    albedo; // The reflecting power of any surface is called Albedo Reflection 
};

struct  s_object
{
    t_object_type   type;
    void            *element;
    void            *next;
    t_color3        albedo; // The reflecting power of the object 
};

typedef struct s_light t_light;
typedef struct s_scene t_scene;

struct s_light
{
    t_point3    origin;
    t_color3    light_color;
    double      bright_ratio;
};

struct s_scene            // Making a new master struct to keep a list of lights and objects 
{
    t_canvas        canvas;
    t_camera        camera;  
    t_object        *world;  // List of objects
    t_object        *light;  // List of light sources 
    t_color3        ambient;
    t_ray           ray;
    t_hit_record    rec;
};




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

#endif