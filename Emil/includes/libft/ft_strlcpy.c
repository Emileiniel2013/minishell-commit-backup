/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:28:01 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/11 19:24:42 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	len;
	size_t	src_len;

	len = 0;
	src_len = 0;
	while (src[src_len] != 0)
		src_len++;
	if (dsize == 0)
		return (src_len);
	while (src[len] != '\0' && len < dsize - 1)
	{
		dst[len] = src [len];
		len++;
	}
	dst[len] = '\0';
	return (src_len);
}
