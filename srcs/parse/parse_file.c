/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:43:49 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/23 13:43:49 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	p_err(char *s)
{
	printf("\033[31mError\033[0m\n%s\n", s);
	exit(1);
}

int	open_file(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		p_err("Usage: ./minirt [filename.rt]");
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
		p_err("file is a directory.");
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		p_err("could not open file");
	return (fd);
}

t_canvas	window_open(char *name, int width, int height)
{
	t_canvas	win;
	int			null;

	win.width = width;
	win.height = height;
	win.ptr = mlx_init();
	win.win = mlx_new_window(win.ptr, width, height, name);
	win.img = mlx_new_image(win.ptr, width, height);
	win.buf = (int *)mlx_get_data_addr(win.img, &null, &null, &null);
	return (win);
}

void	scene_preinit(t_scene *scene)
{
	scene->obj_count = 0;
	scene->light_count = 0;
	scene->cam_count = 0;
	scene->ambient_count = 0;
	scene->canvas = window_open("miniRt", WIDTH, HEIGHT);
}

t_scene	parse(int argc, char **argv)
{
	t_scene		scene;
	const int	fd = open_file(argc, argv);
	char		**split_line;

	scene_preinit(&scene);
	while (1)
	{
		split_line = ft_split(get_next_line(fd), ' ');
		if (split_line == NULL)
			break ;
		if (split_line && *split_line)
			detect_elem(*split_line, split_line + 1, &scene);
		free_splited(split_line, -1);
	}
	close(fd);
	if (scene.light_count < 1)
		p_err("Not enough lights");
	if (scene.cam_count < 1)
		p_err("Camera is missing");
	if (scene.ambient_count < 1)
		p_err("not enough ambient lights");
	scene.world[scene.obj_count].func = NULL;
	return (scene);
}
