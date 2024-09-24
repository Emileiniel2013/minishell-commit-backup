/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:34:23 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/18 11:49:29 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)

{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n > 0)
	{
		*(temp) = 0;
		n--;
		temp++;
	}
}

/*
ft_bzero -- writes 0 to a byte of string
this function is the same as the privious memset function but the difference
is that in the argument c here we have if by default 0.
*/