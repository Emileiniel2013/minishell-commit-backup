/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:45:50 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/11 15:59:17 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	remaining;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= size)
		return (src_len + size);
	remaining = size - dst_len - 1;
	while (*dst)
		dst++;
	while (*src && remaining > 0)
	{
		*dst = *src;
		dst++;
		src++;
		remaining--;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
