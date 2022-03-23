/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaplant <llaplant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:43:30 by llaplant          #+#    #+#             */
/*   Updated: 2022/03/23 13:43:31 by llaplant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <unistd.h>

int ft_strlen(const char *s)
{
	int     i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char    *ft_strjoin(char *s, char c)
{
	char    *out;
	int     n;

	n = 2;
	if (s)
	{
		while (*s && s++)
			n++;
	}
	out = (char *)malloc(n * sizeof(char));
	out[--n] = '\0';
	out[--n] = c;
	if (s)
	{
		while (n--)
			out[n] = *--s;
		free(s);
	}
	return (out);
}

// Updated GNL to do auto free instead of doing Malloc 10000 

char    *get_next_line(int fd)
{
	char		    c;
	static char		*buf;

	buf = NULL;
	if (buf)
		free(buf);
	buf = NULL;
	while (read(fd, &c, 1) && (c != '\n' || buf == NULL))
	{
		if (c == '\n')
			continue ;
		buf = ft_strjoin(buf, c);
	}
	return (buf);
}
