/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 08:37:12 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/01 14:11:40 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../42-libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include "structs.h"

typedef struct s_rt t_rt;
typedef struct s_shapes t_shapes;

struct s_shapes
{
	t_sphere *Sphere;
};

struct s_rt
{
	int fd; //File descriptor
	void    **objects; //I think storing all shapes struct in a single array we can loop through is a good idea, void cause idk the type yet
};

// I like the idea of objects, I will make and object struct, in structs and we can basically parse the info and make a list of object type structs 
int     parse_rgb(char *line);
void    parse_amb(char *line, t_scene *scene);
void    parse_cam(char *line, t_scene *scene);
t_point3	get_pos(char *line);
float		stof(char **str);
t_vec3	get_normal(char *line);
void    parse_cam(char *line, t_scene *scene);
void	parse_light(char *line, t_scene *scene);
void	parse_sphere(char *line, t_scene *scene);
void	parse_plane(char *line, t_scene *scene);
void	parse_cylinder(char *line, t_scene *scene);

#endif