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
    scene->ambient.intensity = ft_atoi(tmp[1]); //need an ascii to float function, also slot 1 cause slot 0 is 'A'
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
        printf("Multiple Camera definitions found! Exiting\n");
        exit(1);
    }
    tmp = ft_split(line, ' ');
    //cam parse
}