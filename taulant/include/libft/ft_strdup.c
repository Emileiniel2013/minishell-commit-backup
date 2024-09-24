/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:39:54 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/19 17:36:28 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	unsigned char	*s2;
	size_t			i;
	size_t			j;

	i = 0;
	while (s1[i])
		i++;
	s2 = malloc(i + 1);
	if (s2 == 0)
		return (NULL);
	j = 0;
	while (s1[j])
	{
		s2[j] = s1[j];
		j++;
	}
	s2[j] = '\0';
	return ((char *)s2);
}
