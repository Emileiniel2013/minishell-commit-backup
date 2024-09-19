/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:35:35 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/21 10:43:56 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	a;
	size_t	b;
	size_t	c;

	a = 0;
	b = 0;
	c = ft_strlen(s);
	if (start >= c)
		return (ft_strdup(""));
	if (len > c - start)
		len = c - start;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (a < start && s[a])
	{
		a++;
	}
	while (s[a] && len > 0 && len--)
	{
		str[b++] = s[a++];
	}
	str[b] = '\0';
	return (str);
}
