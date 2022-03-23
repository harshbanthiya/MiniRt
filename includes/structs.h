/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:23:21 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/03/23 13:42:15 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <math.h>
#include <stdbool.h>

# define PI                 3.14159265358979323846264338327950288
# define TWO_PI             6.28318530717958647692528676655900577
# define PI_TWO             1.57079632679489661923132169163975144
# define EPSILON            0.0001

# define WIDTH              480
# define HEIGHT             480
# define CAMERA_CLIP_START	.01

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
typedef struct s_cylinder   t_cylinder;
typedef struct s_cylinder t_cylinder;

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
	t_vec3      pos;
	t_vec3      normal;      
};

struct  s_cylinder
{
	t_vec3  pos;
	t_vec3  dir;
	float   rad;
	float   height;
	t_vec3  ca;
	float   caca;
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
		t_cylinder  cylinder;
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
	float       intensity;
	int         color;
};

struct  s_ambient
{
	float       intensity;
	int         color;
};

struct s_scene            // Making a new master struct to keep a list of lights and objects 
{
	t_canvas        canvas;
	t_camera        camera;
	int             cam_count; 
	t_object        world[1024];  // List of objects
	int             obj_count;
	t_light         light[64];
	int             light_count;
	t_ambient       ambient;
	int             ambient_count;
	int             keys[1024];
};

typedef struct s_vars_render
{
	t_vec3	dir;
	t_vec3	cam_right;
	t_vec3	cam_up;
	float	half_x;
	float	half_y;
	t_vec3	ray;
	t_vec3	yr;
	t_vec3	xr;
}t_vars_render;

#endif