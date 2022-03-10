/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 09:26:16 by llaplant          #+#    #+#             */
/*   Updated: 2021/05/12 17:00:35 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_malloc_splitted(char ***tab, char *s, char c)
{
	int 	size;
	int 	i;

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

// pass n as -1 to free everything 
int 	free_splited(char **tab, int n)
{
	if (n == -1)
	{
		while(tab[++n])
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

static void 	stcpy(char *dst, char *src, size_t size)
{
	while (--size > 0 && *src)
		*dst++ = *src++;
	*dst = '\0';
}

// Updating split to perform better and free wihtout leaks and made it lightweight

char	**ft_split(char *s, char c)
{
	char			**tab;
	unsigned int	size;
	unsigned int 	n;
	
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
