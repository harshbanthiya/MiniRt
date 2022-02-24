#include "minirt.h"

/* To see the gradient in this, run make, then ./minirt > rgb.ppm and then open rgb.ppm */
/* 
void    write_color(t_color3 pixel_color)
{
    printf("%d %d %d\n", (int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z));
}
*/
/*
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
    return (scene);
} 
*/
void render(const t_scene *scene, const t_canvas *win, 
        const t_camera *cam, int *buf);
        
int	hook_close(t_scene *scene)
{
	mlx_destroy_window(scene->canvas.ptr, scene->canvas.win);
	exit(0);
	return (0);
}
void	make_move(t_scene *scene, int axis, int dist)
{
	t_vec3	dir;
	t_vec3	move;

	dir = radian_to_vector(&scene->camera.rot);
	move = dir;
	if (axis >= 1)
		move = cross(move, (t_vec3){0, 0, 1});
	if (axis == 2)
		move = cross(move, dir);
	move = mult(move, dist);
	scene->camera.pos = add(scene->camera.pos, move);
	render(scene, &scene->canvas, &scene->camera, scene->canvas.buf);
}

int	controls_listen(t_scene *scene)
{
	if (scene->keys[KEY_ESCAPE])
		hook_close(scene);
	if (scene->keys[KEY_W] || scene->keys[KEY_UP])
		make_move(scene, 0, 10);
	if (scene->keys[KEY_S] || scene->keys[KEY_DOWN])
		make_move(scene, 0, -10);
	if (scene->keys[KEY_A] || scene->keys[KEY_LEFT])
		make_move(scene, 1, -10);
	if (scene->keys[KEY_D] || scene->keys[KEY_RIGHT])
		make_move(scene, 1, 10);
	if (scene->keys[KEY_SPACE])
		make_move(scene, 2, 5);
	if (scene->keys[KEY_LSHIFT])
		make_move(scene, 2, -5);
	return (0);
}

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
        if (!ray_scene(&hits->p, &l, scene, hits+ 1)
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


t_canvas    window_open(char *name, int width, int height)
{
    t_canvas    win;
    int         null;

    win.width = width;
    win.height = height;
    win.ptr = mlx_init();
    win.win = mlx_new_window(win.ptr, width, height, name);
    win.img = mlx_new_image(win.ptr, width, height);
    win.buf = (int *)mlx_get_data_addr(win.img, &null, &null, &null);
    return (win);
}
void    controls_init(t_scene *scene)
{
    int i;

    i = -1;
    while (++i < 256)
        scene->keys[i] = 0;
}

t_scene scene_it(void)
{
    t_scene scene;
    scene = (t_scene){.obj_count = 1, .light_count = 1, .cam_count = 1, 
        .ambient_count = 0, .canvas = window_open("miniRt", WIDTH, HEIGHT)};
    scene.ambient.intensity= 0.5;
    scene.ambient.color = ((255 & 255) << 16 | (255 & 255) << 8 | (255 & 255) << 0);
    scene.camera.pos = (t_vec3){0.0, -100.0, 0.0};
    scene.camera.rot = (t_vec3){0.0, 0.0, 0.0};
    scene.camera.width = WIDTH;
    scene.camera.height = HEIGHT;
    scene.camera.fov_pixel = 60.0 / 180.0 * PI / WIDTH;
    scene.light[0].position = (t_vec3){40.0, 0.0, 30.0}; 
    scene.light[0].intensity = 0.5;
    scene.light[0].color = ((255 & 255) << 16 | (255 & 255) << 8 | (255 & 255) << 0);
    scene.world[0].ka = 0.7f;
    scene.world[0].kd = 0.5f;
    scene.world[0].ks = 0.8f;
    scene.world[0].specularity = 16.0f;
    scene.world[0].func = ray_sphere;
    scene.world[0].sphere.center = (t_vec3){0.0, 0.0, 0.0};
    scene.world[0].sphere.radius = 20;
    scene.world[0].color = ((222 & 255) << 16 | (32 & 255) << 8 | (32 & 255) << 0);
    return (scene);
}
int	hook_mouse_move(int x, int y, t_scene *scene)
{
	static int		first = 1;
	static t_vec3	last;

	if (!first)
	{
		scene->camera.rot.x = fmax(fmin(scene->camera.rot.x
					+ (float)(last.y - y) / 50.0f, 1), -1);
		scene->camera.rot.z += (float)(last.x - x) / 50.0f;
		render(scene, &scene->canvas, &scene->camera, scene->canvas.buf);
	}
	first = 0;
	last = (t_vec3){x, y, 0};
	return (1);
}


int	hook_key_down(int key, t_scene *scene)
{
	return (scene->keys[key % 1024] = 1);
}

int	hook_key_up(int key, t_scene *scene)
{
	return (scene->keys[key % 1024] = 0);
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


int main (void)
{
    t_scene     scene;

    scene = scene_it();
    controls_init(&scene);
    render(&scene, &scene.canvas, &scene.camera, scene.canvas.buf);
    mlx_hook(scene.canvas.win, 17, 0, hook_close, (void *)&scene);
	mlx_hook(scene.canvas.win, 6, 64, hook_mouse_move, (void *)&scene);
	mlx_hook(scene.canvas.win, 2, 1L << 0, hook_key_down, (void *)&scene);
	mlx_hook(scene.canvas.win, 3, 1L << 1, hook_key_up, (void *)&scene);
	mlx_loop_hook(scene.canvas.ptr, controls_listen, &scene);
	mlx_loop(scene.canvas.ptr);
	return (0);
    return (0);
}