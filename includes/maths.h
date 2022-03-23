/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:44:29 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/23 13:46:30 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>

static inline int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

static inline unsigned int	rgbmult(unsigned int color, int fac)
{
	if (fac < 0)
		return (0);
	return (
		((((color & (255 << 16)) * fac) & (255 << 24))
			| (((color & (255 << 8)) * fac) & (255 << 16))
			| (((color & (255 << 0)) * fac) & (255 << 8))) >> 8
	);
}

static inline unsigned int	rgbmatrix(unsigned int a, unsigned int b)
{
	return (
		((((a >> 16) * (b >> 16)) >> 8) << 16)
		| (((((a >> 8) & 255) * ((b >> 8) & 255)) >> 8) << 8)
		| ((((a & 255) * (b & 255))) >> 8)
	);
}

static inline unsigned int	rgbadd(unsigned int a, unsigned int b)
{
	return (
		(min((a >> 16) + (b >> 16), 255) << 16)
		| (min(((a >> 8) & 255) + ((b >> 8) & 255), 255) << 8)
		| min((a & 255) + (b & 255), 255)
	);
}

static inline float	sign(float v)
{
	if (v == 0)
		return (0);
	if (v > 0)
		return (1);
	return (-1);
}

#endif 