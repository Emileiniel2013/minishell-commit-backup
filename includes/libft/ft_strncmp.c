/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:16:43 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/19 13:15:48 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n < 1)
		return (0);
	while (*s1 == *s2 && *s1 && *s2 && --n)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2 || n == 0)
		return (0);
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
