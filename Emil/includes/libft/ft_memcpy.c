/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:52:34 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/11 15:58:24 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		a;

	dest_ptr = dst;
	src_ptr = src;
	a = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (a < n)
	{
		dest_ptr[a] = src_ptr[a];
		a++;
	}
	return (dst);
}
