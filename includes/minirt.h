/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 08:37:12 by llaplant          #+#    #+#             */
/*   Updated: 2022/04/07 09:34:06 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include "structs.h"
# include "maths.h"
# include "ray.h"
# include "vector.h"

char			*get_next_line(int fd);
int				free_splited(char **tab, int n);
char			**ft_split(const char *s, char c);
int				ft_strlen(char *str);
int				check_rt(char *str);
void			parse_amb(t_scene *scene, t_ambient ambient);
void			parse_cam(t_scene *scene, t_camera cam);
void			parse_light(t_scene *scene, t_light light);
void			parse_obj(t_scene *scene, t_object obj);
t_vec3			p_n(t_vec3 p_no);
t_scene			parse(int argc, char **argv);
void			detect_elem(char *type, char **arg, t_scene *scene);
void			p_err(char *s);
void			render(const t_scene *scene, const t_canvas *win,
					const t_camera *cam, int *buf);
int				hook_key_up(int key, t_scene *scene);
int				hook_close(t_scene *scene);
int				hook_mouse_move(int x, int y, t_scene *scene);
int				hook_key_down(int key, t_scene *scene);
void			controls_init(t_scene *scene);
int				controls_listen(t_scene *scene);
void			make_move(t_scene *scene, int axis, int dist);

static inline t_vec3	radian_vector_rotation(const t_vec3 *rot)
{
	float	sin_z;
	float	cos_z;
	float	sin_y;
	float	sin_x;
	float	cos_x;

	sin_z = sinf(rot->z);
	cos_z = cosf(rot->z);
	sin_y = sinf(rot->y);
	sin_x = sinf(rot->x);
	cos_x = cosf(rot->x);
	return ((t_vec3){
		-cos_z * sin_y * sin_x - sin_z * cos_x,
		-sin_z * sin_y * sin_x + cos_z * cos_x,
		cosf(rot->y) * sin_x
	});
}

static inline float	dist(const t_vec3 *a, const t_vec3 *b)
{
	return (sqrt((a->x - b->x) * (a->x - b->x)
			+ (a->y - b->y) * (a->y - b->y)
			+ (a->z - b->z) * (a->z - b->z)));
}

static inline float	size(const t_vec3 *a)
{
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
}

static inline t_vec3	reflect(const t_vec3 *l, const t_vec3 *normal)
{
	const float	cos_theta = dot(*l, *normal) / (size(l) * size(normal));

	return (sub(mult(*normal, cos_theta * 2), *l));
}

#endif
