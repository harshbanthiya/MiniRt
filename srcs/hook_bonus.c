/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:42:54 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/23 13:42:54 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	hook_close(t_scene *scene)
{
	mlx_destroy_window(scene->canvas.ptr, scene->canvas.win);
	exit(0);
	return (0);
}

int	hook_key_down(int key, t_scene *scene)
{
	return (scene->keys[key % 1024] = 1);
}

int	hook_key_up(int key, t_scene *scene)
{
	return (scene->keys[key % 1024] = 0);
}
