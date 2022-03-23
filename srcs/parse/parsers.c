/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:43:57 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/23 13:43:57 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"


void    parse_amb(t_scene *scene, t_ambient ambient)
{
	if (scene->ambient_count == 1)
		p_err("too many ambient lights");
	scene->ambient = ambient;
	scene->ambient_count++;
}

void    parse_cam(t_scene *scene, t_camera cam)
{
	if (scene->cam_count == 1)
		p_err("too many cameras");
	scene->camera = cam;
	scene->cam_count++;
}

void	parse_light(t_scene *scene, t_light light)
{
	if (scene->light_count == 62)
		p_err("too many lights");
	scene->light[scene->light_count++] = light;
}

void	parse_obj(t_scene *scene, t_object obj)
{
	if (scene->obj_count == 1022)
		p_err("too many objects");
	obj.ka = 0.7f;
	obj.kd = 0.5f;
	obj.ks = 0.8;
	obj.specularity = 16.0f;
	scene->world[scene->obj_count++] = obj;
}
// Testing the below cylinder function but I merged sphere and plane functions into the parse_obj



/*
void	parse_sphere(char *line, t_scene *scene)
{
	char **tmp;

	tmp = NULL;
	tmp = ft_split(line, ' ');
	scene->world[scene->obj_count].sphere.radius = stof(&tmp[2]); //radius value
	scene->world[scene->obj_count].sphere.center = get_pos(tmp[1]); //coords after sp indicator
	scene->world[scene->obj_count].color = parse_rgb(tmp[3]); //rgb
	free(tmp);
	scene->obj_count++;
}

void	parse_plane(char *line, t_scene *scene)
{
	char **tmp;

	tmp = NULL;
	tmp = ft_split(line, ' ');
	scene->world[scene->obj_count].plane.pos = get_pos(tmp[1]); //coords
	scene->world[scene->obj_count].plane.normal = get_normal(tmp[2]); //orientation, I again need to make a separate func for -1-1 values
	scene->world[scene->obj_count].color = parse_rgb(tmp[3]); //rgb
	free(tmp);
	scene->obj_count++;
}


*/