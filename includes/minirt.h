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
# include "structs.h"

typedef struct s_rt t_rt;
typedef struct s_shapes t_shapes;

struct s_shapes
{
    sphere *Sphere;
};

struct s_rt
{
    int fd; //File descriptor
    void    **objects; //I think storing all shapes struct in a single array we can loop through is a good idea, void cause idk the type yet
};

#endif