/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:43:41 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/31 08:52:08 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	stof(char ***str)
{
	char	*s;
	int		point;
	double	dec;
	double	exp;
	int		neg;

	s = *(*str)++;
	if (s == NULL)
		p_err("missing float");
	dec = 0;
	point = 0;
	exp = 1;
	neg = (*s == '-' && s++) * 2 - 1;
	while (*s)
	{
		if (point)
			exp *= 10;
		if (*s >= '0' && *s <= '9')
			dec = dec * 10.0 - *s++ + '0';
		else if (*s != '.' || point)
			p_err("invalid number");
		else
			point = (1 && s++);
	}
	return (dec * neg / exp);
}

static t_vec3	vec(char ***args)
{
	t_vec3		ret;
	char		**tmp;

	if (**args == NULL)
		p_err("missing vector");
	tmp = ft_split(**args, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
		p_err("invalid vector");
	ret = (t_vec3){stof(&tmp), stof(&tmp), stof(&tmp)};
	free_splited(tmp - 3, -1);
	(*args)++;
	return (ret);
}

static int	parse_rgb(char ***args)
{
	char	**tmp;
	int		color;

	if (**args == NULL)
		p_err("missing color");
	tmp = ft_split(**args, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
		p_err("invalid color");
	if (tmp[0][0] == '-' || tmp[1][0] == '-' || tmp[2][0] == '-')
		p_err("invalid color");
	color = ((int)stof(&tmp) & 255) << 16
		| ((int)stof(&tmp) & 255) << 8
		| ((int)stof(&tmp) & 255) << 0;
	free_splited(tmp - 3, -1);
	(*args)++;
	return (color);
}

void	parse_cylinder(char ***arg, t_scene *scene)
{
	t_cylinder	cylinder;

	cylinder.pos = vec(arg);
	cylinder.dir = vec(arg);
	cylinder.rad = stof(arg) / 2.0 ;
	cylinder.height = stof(arg);
	cylinder.ca = sub(add(cylinder.pos, \
		mult(cylinder.dir, cylinder.height)), cylinder.pos);
	cylinder.caca = dot2(cylinder.ca);
	parse_obj(scene, (t_object){.func = ray_cylinder,
		.cylinder = cylinder, .color = parse_rgb(arg)});
}

void	detect_elem(char *type, char **arg, t_scene *scene)
{
	if (type[0] == 'A' && type[1] == '\0')
		parse_amb(scene, (t_ambient){stof(&arg), parse_rgb(&arg)});
	else if (type[0] == 'C' && type[1] == '\0')
		parse_cam(scene, (t_camera){vec(&arg), vec(&arg),
			WIDTH, HEIGHT, stof(&arg) / 180.0 * PI / WIDTH});
	else if (type[0] == 'L' && type[1] == '\0')
		parse_light(scene, (t_light){vec(&arg), stof(&arg),
			parse_rgb(&arg)});
	else if (type[0] == 's' && type[1] == 'p' && type[2] == '\0')
		parse_obj(scene, (t_object){.func = ray_sphere, .sphere
			= (t_sphere){vec(&arg), stof(&arg)}, .color = parse_rgb(&arg)});
	else if (type[0] == 'p' && type[1] == 'l' && type[2] == '\0')
		parse_obj(scene, (t_object){.func = ray_plane, .plane
			= (t_plane){vec(&arg), vec(&arg)}, .color = parse_rgb(&arg)});
	else if (type[0] == 'c' && type[1] == 'y' && type[2] == '\0')
		parse_cylinder(&arg, scene);
	else
		p_err("invalid object type");
	if (*arg)
		p_err("too many fields");
}
