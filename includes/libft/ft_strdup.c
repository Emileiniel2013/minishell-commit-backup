/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:29:22 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/05 14:40:14 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		j;
	char	*cpy;

	j = 0;
	cpy = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!cpy)
		return (NULL);
	while (*s1)
	{
		cpy[j] = *s1;
		s1++;
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}
