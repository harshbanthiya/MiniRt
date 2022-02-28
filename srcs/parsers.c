#include "../includes/minirt.h"
#include "../includes/structs.h"

void    parse_amb(char *line, t_scene *scene)
{
	char **tmp;

	tmp = NULL;
	if (scene->ambient.set != 1)
		scene->ambient.set = 1; //for detection of multiple of them in .rt file
	else
	{
		//fallback multiple
		printf("Multiple Ambiant definitions detected! Exiting\n");
		exit(1);
	}
	tmp = ft_split(line, ' ');
	//scene->ambient.intensity = ft_atoi(tmp[1]); //need an ascii to float function, also slot 1 cause slot 0 is 'A'
	scene->ambient.intensity = atof(tmp[1]); //temporary use of stdio func atof
	scene->ambient.color = parse_rgb(tmp[2]);
	free(tmp);
}

void    parse_cam(char *line, t_scene *scene)
{
	char    **tmp;

	tmp = NULL;
	if (scene->camera.set != 1)
		scene->camera.set = 1;
	else
	{
		//fallback multiple
		printf("Multiple Camera definitions found! Exiting\n");
		exit(1);
	}
	tmp = ft_split(line, ' ');
	scene->camera.pos = get_pos(tmp[1]); //tmp[1] is the xyz coords in the strings
	scene->camera.rot = get_pos(tmp[2]); //need to implement checks for -1-1
	scene->camera.fov_pixel = atof(tmp[3]);
	free(tmp);
	//cam parse
}

void	parse_light(char *line, t_scene *scene)
{
	char **tmp;

	tmp = NULL;
	if (scene->light.set != 1)
		scene->light.set = 1;
	else
	{
		//fallback multiple
		printf("Multiple Light defintions found! Exiting\n");
		exit(1);
	}
	tmp = ft_split(line, ' ');
	scene->light.position = get_pos(tmp[1]);
	scene->light.intensity = atof(tmp[2]);
	scene->light.color = parse_rgb(line); //not used in mandatory
	free(tmp);
}