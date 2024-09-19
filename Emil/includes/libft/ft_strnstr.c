/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:04:27 by temil-da          #+#    #+#             */
/*   Updated: 2024/04/14 19:43:16 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	const char	*x;
	const char	*y;
	size_t		original_len;

	if (*needle == '\0')
		return ((char *)hay);
	while (*hay && len > 0)
	{
		original_len = len;
		x = needle;
		y = hay;
		while (*x == *y && *x && len > 0)
		{
			x++;
			y++;
			len--;
		}
		if (*x == '\0')
			return ((char *)hay);
		hay++;
		len = original_len - 1;
	}
	return (NULL);
}
