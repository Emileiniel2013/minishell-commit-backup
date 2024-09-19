/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:35:52 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/08 16:24:26 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t				a;
	unsigned char		*p;

	a = 0;
	p = (unsigned char *)b;
	while (a < len)
	{
		*p = (unsigned char)c;
		p++;
		a++;
	}
	return (b);
}
