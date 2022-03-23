/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:42:00 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/23 13:42:05 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H 

# include "vector_operators.h"
# include "structs.h"

static inline t_vec3 normalize(const t_vec3 vec)
{
	return (mult(vec, 1.0f
			/ sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)));
}

static inline float dot(const t_vec3 a, const t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline float dot2(const t_vec3 v)
{
	return (dot(v, v));
}

static inline t_vec3 cross(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

#endif 