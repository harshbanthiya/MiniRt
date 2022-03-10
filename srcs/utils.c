#include "../includes/structs.h"
#include "../includes/minirt.h"

/*
void		next(char **str)
{
	while (**str == 32 || **str == 9)
		(*str)++;
}
*/

/* 
t_point3	get_pos(char *line)
{
	t_point3	ret;
	char		**tmp;

	tmp = NULL;
	tmp = ft_split(line, ',');
	//We really need an atof function
	ret.x = stof(&tmp[0]);
	ret.y = stof(&tmp[1]);
	ret.z = stof(&tmp[2]);
	free(tmp);
	return ret;
}

t_vec3	get_normal(char *line)
{
	t_vec3	ret;
	char	**tmp;

	tmp = NULL;
	tmp = ft_split(line, ',');
	ret.x = stof(&tmp[0]);
	ret.y = stof(&tmp[1]);
	ret.z = stof(&tmp[2]);
	free(tmp);
	if ((ret.x >= -1 && ret.x <= 1) && (ret.y >= -1 && ret.y <= 1) && (ret.z >= -1 && ret.z <= 1))
		return (ret);
	else
	{
		printf("Illegal value!!! should be between -1 and 1!!\n");
		ret.x = -2;
		ret.y = -2;
		ret.z = -2;
		return (ret);
		//need better error handling here
	}
}
*/