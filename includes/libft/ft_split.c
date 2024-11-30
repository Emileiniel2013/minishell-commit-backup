/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:53:57 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/13 16:32:44 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_count_strings(char const *s, char c);
static int		ft_malloc(char **strings, int position, size_t size);
static int		ft_write_strings(char **strings, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	strings;
	char	**char_arr;

	if (!s)
		return (NULL);
	strings = 0;
	strings = ft_count_strings(s, c);
	char_arr = malloc(sizeof(char *) * (strings + 1));
	if (!char_arr)
		return (NULL);
	char_arr[strings] = NULL;
	if (ft_write_strings(char_arr, s, c) > 0)
		return (NULL);
	return (char_arr);
}

static size_t	ft_count_strings(char const *s, char c)
{
	size_t	strings;
	int		inside_string;

	strings = 0;
	while (*s)
	{
		inside_string = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			if (inside_string == 0)
			{
				++strings;
				inside_string = 1;
			}
			++s;
		}
	}
	return (strings);
}

static int	ft_malloc(char **strings, int position, size_t size)
{
	int	a;

	a = 0;
	strings[position] = malloc(size);
	if (!strings[position])
	{
		while (a < position)
		{
			free (strings[a]);
			a++;
		}
		free (strings);
		return (1);
	}
	return (0);
}

static int	ft_write_strings(char **strings, char const *s, char c)
{
	size_t	len;
	int		a;

	a = 0;
	while (*s)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (ft_malloc(strings, a, len + 1) > 0)
				return (1);
			ft_strlcpy(strings[a], s - len, len + 1);
		}
		a++;
	}
	return (0);
}
