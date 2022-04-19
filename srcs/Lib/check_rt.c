/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:49:41 by llaplant          #+#    #+#             */
/*   Updated: 2022/04/19 10:11:39 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	stcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

int	check_rt(char *str)
{
	char	ext[3];
	int		len;

	len = ft_strlen(str);
	ext[0] = str[len - 3];
	ext[1] = str[len - 2];
	ext[2] = str[len - 1];
	if (stcmp(ext, ".rt") != 0)
	{
		return (1);
	}
	else
		return (0);
}
