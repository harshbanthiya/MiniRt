#include "../includes/minirt.h"
#include "../includes/structs.h"

/* Eventually, I need to implement proper handling of illegal value. Probably will code some kind of function that will go
through everything and if something is illegal, exit the program. But for now this will be enough to get the thing
running
*/

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
	scene->ambient.intensity = stof(&tmp[1]); //temporary use of stdio func atof
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
	scene->camera.rot = get_normal(tmp[2]); //need to implement checks for -1-1
	scene->camera.fov_pixel = stof(&tmp[3]);
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
	scene->light.intensity = stof(&tmp[2]);
	scene->light.color = parse_rgb(line); //not used in mandatory
	free(tmp);
}

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

void	parse_cylinder(char *line, t_scene *scene)
{
	char **tmp;

	tmp = NULL;
	tmp = ft_split(line, ' ');
	scene->world[scene->obj_count].cylinder.pos = get_pos(tmp[1]); //coords
	scene->world[scene->obj_count].cylinder.normal = get_normal(tmp[2]); 
	scene->world[scene->obj_count].cylinder.diameter = stof(&tmp[3]); //diameter
	scene->world[scene->obj_count].cylinder.height = stof(&tmp[4]); //height
	scene->world[scene->obj_count].color = parse_rgb(tmp[5]); //rgb
	free(tmp);
	scene->obj_count++;
}
