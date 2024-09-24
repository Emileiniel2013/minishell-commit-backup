/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:39:06 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/24 16:58:53 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	w_counter(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
			{
				i++;
			}
			j++;
		}
	}
	return (j);
}

static char	**free_s(char **str, int index)
{
	while (index >= 0)
	{
		free(str[index]);
		index--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		start;
	int		end;
	int		i;
	char	**str;

	start = 0;
	end = 0;
	i = 0;
	str = (char **)ft_calloc(w_counter(s, c) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (i < w_counter(s, c) && s[start])
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end] != '\0')
			end++;
		str[i] = ft_substr(s, start, end - start);
		if (str[i] == NULL)
			return (free_s(str, i));
		start = end;
		i++;
	}
	return (str);
}
/*this function splits a string in to a arrray of substrings 
based on limit of character and will take a pointer to the to input the s

*/