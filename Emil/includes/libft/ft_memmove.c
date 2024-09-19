/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:49:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/08 18:47:33 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		a;

	dest_ptr = dst;
	src_ptr = src;
	a = 0;
	if (dest_ptr < src_ptr)
	{
		while (a < len)
		{
			dest_ptr[a] = src_ptr[a];
			a++;
		}
	}
	else if (dest_ptr > src_ptr)
	{
		a = len;
		while (a > 0)
		{
			dest_ptr[a - 1] = src_ptr[a - 1];
			a--;
		}
	}
	return (dst);
}
