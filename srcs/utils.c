#include "../includes/structs.h"
#include "../includes/minirt.h"

/* vec3 constructor */
t_vec3 vec3(double x, double y, double z)
{
	t_vec3  v;

	v.x = x;
	v.y = y;
	v.z = z;

	return (v);   
}

/* point 3 constructor */
t_point3 point3(double x, double y, double z)
{
	t_point3    point;

	point.x = x;
	point.y = y;
	point.z = z;

	return (point);
}

/* color constructor */
t_point3 color3(double r, double g, double b)
{
	t_color3    color;

	color.x = r;
	color.y = g;
	color.z = b;

	return (color);
}

/* Below are some vector standard functions */

/* set vector value */

void    vset(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

/*  Finding Vector Length */
/*  The length of a vector is the square root of the sum of 
	the squares of all x y z components.
*/

double vlength2(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double  vlength(t_vec3 vec)
{
	return (sqrt(vlength2(vec)));
}

/* Vector addition */

t_vec3  vadd(t_vec3 v1, t_vec3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	
	return (v1);
}

t_vec3 vadd_(t_vec3 vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	
	return (vec);
}
/* Vector Substraction */

t_vec3  vminus(t_vec3 v1, t_vec3 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	
	return (v1);
}

t_vec3 vminus_(t_vec3 vec, double x, double y, double z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	
	return (vec);
}

/* Vector Multiplication */

t_vec3 vmult(t_vec3 v1, t_vec3 v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	
	return (v1);
}

t_vec3 vmult_(t_vec3 v, double n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;

	return (v);
}

/* Vector Division */

t_vec3 vdivide(t_vec3 v, double n)
{
	v.x *= 1 / n;
	v.y *= 1 / n;
	v.z *= 1 / n;

	return (v);
}

/* Vector Dot Product */

double vdot(t_vec3 v1, t_vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/* Vector Cross Product */

t_vec3 vcross(t_vec3 v1, t_vec3 v2)
{
	t_vec3  r;

	r.x = (v1.y * v2.z) - (v1.z * v2.y);
	r.y = (v1.z * v2.x) - (v1.x * v2.z);
	r.z = (v1.x * v2.y) - (v1.y * v2.x);
	
	return (r);
}

/* Unit Vector */

t_vec3 vunit(t_vec3 v)
{
	double  len;

	len = vlength(v);
	if (len == 0)
	{
		printf("Error. Cannot divide by zero\n");
		exit(0);
	}
	v.x /= len;
	v.y /= len;
	v.z /= len;
	
	return (v);
}

/* Vector Minimum */

t_vec3 vmin(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

/* Object Utility functions */
//these need fixing
void    objadd(t_object **list, t_object *new)
{
	t_object *curr;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	curr = *list;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

t_object *olast(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int parse_rgb(char *line)
{
	char **tmp;

	tmp = NULL;
	tmp = ft_split(line, ",");
	return ((ft_atoi(tmp[0]) & 255) << 16 | (ft_atoi(tmp[1]) & 255) << 8 | (ft_atoi(tmp[2]) & 255) << 0);
}

t_point3	get_pos(char *line)
{
	t_point3	ret;
	char		**tmp;

	tmp = NULL;
	tmp = ft_split(line, ',');
	//We really need an atof function
	ret.x = atof(tmp[0]);
	ret.y = atof(tmp[1]);
	ret.z = atof(tmp[2]);
	free(tmp);
	return ret;
}