/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operators.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:42:11 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/23 13:42:12 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_OPERATORS_H
# define VECTOR_OPERATORS_H

# include "structs.h"

static inline t_vec3	sub(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

static inline t_vec3	add3(const t_vec3 a, const t_vec3 b, const t_vec3 c)
{
	return ((t_vec3)
		{
			a.x + b.x + c.x,
			a.y + b.y + c.x,
			a.z + b.z + c.z
		});
}

static inline t_vec3	add(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

static inline t_vec3	mult(const t_vec3 a, const float fac)
{
	return ((t_vec3){a.x * fac, a.y * fac, a.z * fac});
}

#endif
