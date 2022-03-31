/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 09:26:16 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/31 08:36:43 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_malloc_splitted(char ***tab, const char *s, char c)
{
	int		size;
	int		i;

	size = 1;
	i = 0;
	while (s[i])
	{
		if (s[i++] != c && size++)
		{
			while (s[i] && s[i] != c)
				i++;
		}
	}
	*tab = malloc(size * sizeof(char *));
	return (*tab == NULL);
}

int	free_splited(char **tab, int n)
{
	if (n == -1)
	{
		while (tab[++n])
			free(tab[n]);
	}
	else
	{
		while (n--)
			free(tab[n]);
	}
	free(tab);
	return (1);
}

static void	stcpy(char *dst, const char *src, size_t size)
{
	while (--size > 0 && *src)
		*dst++ = *src++;
	*dst = '\0';
}

char	**ft_split(const char *s, char c)
{
	char			**tab;
	unsigned int	size;
	unsigned int	n;

	if (s == NULL || ft_malloc_splitted(&tab, s, c))
		return (NULL);
	n = 0;
	while (*s)
	{
		if (*s++ != c)
		{
			size = 1;
			while (*s && *s != c && size++)
				s++;
			tab[n] = malloc(sizeof(char) * (size + 1));
			if (tab[n] == NULL && free_splited(tab, n))
				return (NULL);
			stcpy(tab[n++], s - size, size + 1);
		}
	}
	tab[n] = NULL;
	return (tab);
}
