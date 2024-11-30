/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:29:59 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/11 18:35:41 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;

	str = NULL;
	while (*s)
	{
		if (*s == (char)c)
			str = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return ((char *)str);
}
