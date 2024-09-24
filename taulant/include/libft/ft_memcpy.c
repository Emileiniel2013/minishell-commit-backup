/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:34:42 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/22 17:20:20 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*p_dst;
	const char	*p_src;
	size_t		i;

	p_dst = (char *)dst;
	p_src = (char *)src;
	i = 0;
	if ((p_dst == NULL) && (p_src == NULL))
		return (NULL);
	while (i < n)
	{
		p_dst[i] = p_src[i];
		i++;
	}
	return ((void *)dst);
}

/*this function copy memory area// in this function it is usful 
to copy a number of bytes from one place of memory area (src) to another place
 * in memory area (dst)
 * this function takes 3 arguments :  1-> dst : its a void pointer in which we 
 * are going to store the new string whith the moved bbytes
 * 2 -> src : its a pointer which it shows in the memory direction which is 
 * the string that you will be moving the bytes
 * 3 -> len : its the argument that shows you how meny bytes you are 
 * going to move in memory.
 * in the begining we will initialize 2 temporary ointer for src and dst
 *  we will make the temporary pointers that we create equal to dst and src 
 * converted as an UNSIGNED CHAR;
 *  do a check if src and dst are null and return dst;;
 *  loop through the pointers until we didnt reach the 
 * value of n(number o bytes we need to copy)
 *  in this part we will copy bytrs from src to dst
 *  in the end we return the dst;
 * */