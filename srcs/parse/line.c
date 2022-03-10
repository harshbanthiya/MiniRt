#include "minirt.h"


// Slightly upgrading the stof function to suit all situations removed all the extra while loops 
// and fit everything in one while loop by adding two variables. 

static float    stof(char ***str)
{
    char    *s;
    int     point;
	double	dec;
    double  exp;
	int		neg;

	s = *(*str)++;
    if (s == NULL)
        p_err("missing float");
	dec = 0;
    point = 0;
    exp =  1;
    neg = (*s == '-' && s++) * 2 - 1; //if (**str == '-' && *((*str)++)) // neg = -1; // quite proud of that statement haha. it is the same thing you did in a sentence
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

// changed get_pos to vec cause we need to make a vec from string 

static t_vec3	vec(char ***args)
{
	t_vec3      ret;
	char		**tmp;

    if (**args == NULL)
        p_err("missing vector");
    tmp = ft_split(**args, ',');
    if (!tmp || !tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
        p_err("invalid vector");
	ret.x = stof(&tmp);
	ret.y = stof(&tmp);
	ret.z = stof(&tmp);
	free_splited(tmp - 3, -1);
    (*args)++;
	return (ret);
}

static int parse_rgb(char ***args)
{
	char    **tmp;
    int     color;

    if (**args == NULL)
        p_err("missing color");
    tmp = ft_split(**args, ',');
    if (!tmp || !tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
        p_err("invalid color");
    color = ((int)stof(&tmp) & 255) << 16 
        | ((int)stof(&tmp) & 255) << 8 
        | ((int)stof(&tmp) & 255) << 0;
    free_splited(tmp - 3, -1);
    (*args)++;
    return (color);
}


void 	detect_elem(char *type, char **arg, t_scene *scene)
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
    //else if (type[0] == 'c' && type[1] == 'y' && type[2] == '\0')
      //  parse_cylinder(&arg, scene);
    else 
        p_err("invalid object type");
    if (*arg)
        p_err("too many fields");    
}