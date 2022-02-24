#include "../includes/minirt.h"
#include "../includes/structs.h"

void    parse_amb(char *line, t_scene *scene)
{
    char **tmp;

    tmp = NULL;
    tmp = ft_split(line, ' ');
    scene->amb.amb_val = ft_atoi(tmp[1]); //need an ascii to float function, also slot 1 cause slot 0 is 'A'
}