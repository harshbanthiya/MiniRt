/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:42:41 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/23 13:42:42 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

void controls_init(t_scene *scene)
{
    int     i;

    i = -1;
    while (++i < 256)
        scene->keys[i] = 0;
}

void	make_move(t_scene *scene, int axis, int dist)
{
	t_vec3	dir;
	t_vec3	move;

	dir = radian_vector_rotation(&scene->camera.rot);
	move = dir;
	if (axis >= 1)
		move = cross(move, (t_vec3){0, 0, 1});
	if (axis == 2)
		move = cross(move, dir);
	move = mult(move, dist);
	scene->camera.pos = add(scene->camera.pos, move);
	render(scene, &scene->canvas, &scene->camera, scene->canvas.buf);
}

int controls_listen(t_scene *scene)
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