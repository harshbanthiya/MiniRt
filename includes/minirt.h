/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 08:37:12 by llaplant          #+#    #+#             */
/*   Updated: 2022/02/16 08:45:41 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../42-libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include "structs.h"
# include "maths.h"
# include "ray.h"
# include "vector.h"

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

static  inline t_vec3 radian_to_vector(const t_vec3 *rot)
{
    float   sin_z;
    float   cos_z;
    float   sin_y;
    float   sin_x;
    float   cos_x;

    sin_z = sinf(rot->z);
    cos_z = cosf(rot->z);
    sin_y = sinf(rot->y);
    sin_x = sinf(rot->x);
    cos_x = cosf(rot->x);
    return ((t_vec3){
        -cos_z * sin_y * sin_x - sin_z * cos_x,
        -sin_z * sin_y * sin_x + cos_z * cos_x,
        cosf(rot->y) * sin_x
    });
}

static inline float dist(const t_vec3 *a, const t_vec3 *b)
{
    return (sqrt((a->x - b->x) * (a->x - b->x)
            + (a->y - b->y) * (a->y - b->y)
            + (a->z - b->z) * (a->z - b->z)));
}

static inline float size(const t_vec3 *a)
{
    return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
}

static inline t_vec3 reflect(const t_vec3 *l, const t_vec3 *normal)
{
    const float cos_theta = dot(*l, *normal) / (size(l) * size(normal));
    return (sub(mult(*normal, cos_theta * 2), *l));
} 

#endif
