/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:33:12 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/03/30 20:33:15 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hook_mouse_move(int x, int y, t_scene *scene)
{
	(void) x;
	(void) y;
	(void) scene;
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
