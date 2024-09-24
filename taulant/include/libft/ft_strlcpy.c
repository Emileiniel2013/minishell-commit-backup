/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:35:22 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/22 14:52:48 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	sl;

	sl = 0;
	sl = ft_strlen(src);
	if (dstsize == 0)
		return (sl);
	if (sl + 1 < dstsize)
		ft_memcpy(dst, src, sl + 1);
	else
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (sl);
}
/*

ft_strlcpy() --> copy byte of string
this function copies on string to another but always catching the NULL-terminate.

*/