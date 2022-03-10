#include "minirt.h"

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

static inline int   ray_reflect(const t_light *light, const t_vec3 *ray,
        const t_hit_record *hit, const t_vec3 *l)
{
    float   i_diff;
    float   i_spec;
    float   r_dot;
    t_vec3  r;
    t_vec3  v;

    i_diff = light->intensity * hit->obj->kd * dot (*l, hit->normal);
    i_spec = light->intensity * hit->obj->ks; 
    r = reflect(l, &hit->normal);
    v = mult(*ray, -1.0f);
    r_dot = dot(r, v);
    return (rgbmult(light->color, 
                255.0 * (i_diff + i_spec * powf(r_dot, hit->obj->specularity))));
}

static inline unsigned int ray_color(const t_vec3 *orig, 
        const t_vec3 *ray, const t_scene *scene, int rec)
{
    t_hit_record    hits[2];
    t_vec3          l;
    int             i;
    int             col;

    if (!ray_scene(orig, ray, scene, hits))
        return(scene->ambient.color);
    col = rgbmult(scene->ambient.color, 
                255.0 * scene->ambient.intensity * hits->obj->ka);
    i = scene->light_count;
    while (i--)
    {
        l = normalize(sub(scene->light[i].position, hits->p));
        if (!ray_scene(&hits->p, &l, scene, hits + 1)
            || hits[1].dist > dist(&scene->light[i].position, &hits->p))
            col = rgbadd(col, ray_reflect(scene->light + i, ray, hits, &l));
    }
    if (--rec < 0)
        return (rgbmatrix(hits->obj->color, col));
    l = normalize(sub(scene->camera.pos, hits->p));
    l = reflect(&l, &hits->normal);
    return (rgbmatrix(hits->obj->color, rgbadd(col,
                rgbmult(ray_color(&hits->p, &l, scene, rec), 128))));
}


void render(const t_scene *scene, const t_canvas *win, 
        const t_camera *cam, int *buf)
{
    t_vars_render t;
    register int  y;
    register int  x;

    t.dir = radian_to_vector(&cam->rot);
    t.cam_right = normalize(cross(t.dir, (t_vec3){0, 0, 1}));
    t.cam_up = normalize(cross(t.cam_right, t.dir));
    t.half_x = cam->width / 2.0;
    t.half_y = cam->height / 2.0;
    y = cam->height;
    while (y--)
    {
        t.yr = mult(t.cam_up, (y - t.half_y) * cam->fov_pixel);
        x = cam->width;
        while (x--)
        {
            t.xr = mult(t.cam_right, (t.half_x - x) * cam->fov_pixel);
            t.ray = normalize(add3(t.dir, t.xr, t.yr));
            *buf++ = ray_color(&cam->pos, &t.ray, scene, 2);
        }
    }
    mlx_put_image_to_window(win->ptr, win->win, win->img, 0, 0);
}


int main (int argc, char **argv)
{
    t_scene     scene;

    scene = parse(argc, argv);
    controls_init(&scene);
    render(&scene, &scene.canvas, &scene.camera, scene.canvas.buf);
    mlx_hook(scene.canvas.win, 17, 0, hook_close, (void *)&scene);
	mlx_hook(scene.canvas.win, 6, 64, hook_mouse_move, (void *)&scene);
	mlx_hook(scene.canvas.win, 2, 1L << 0, hook_key_down, (void *)&scene);
	mlx_hook(scene.canvas.win, 3, 1L << 1, hook_key_up, (void *)&scene);
	mlx_loop_hook(scene.canvas.ptr, controls_listen, &scene);
	mlx_loop(scene.canvas.ptr);
	return (0);
}