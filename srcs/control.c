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

void	controls_init(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < 256)
		scene->keys[i] = 0;
}

int	controls_listen(t_scene *scene)
{
	if (scene->keys[KEY_ESCAPE])
		hook_close(scene);
	return (0);
}
