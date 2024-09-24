/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:35:02 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/22 17:24:23 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*p_dst;
	char		*p_src;

	p_dst = (char *)dst;
	p_src = (char *)src;
	if ((p_dst == NULL) && (p_src == NULL))
		return (NULL);
	if (p_dst > p_src)
	{
		while (len--)
		{
			p_dst[len] = p_src[len];
		}
	}
	else
	{
		while (len--)
		{
			*p_dst = *p_src;
			p_dst++;
			p_src++;
		}
	}
	return (dst);
}

/*this function is used to move a part of the bytes on memory in another
part of the memory inside that same memory without  having conflict 
in memory and =handeling the overlapping problem inside of the memory.
 * this function it has 3 argument : 1-> dst : its a void pointer in which 
 we are going to store the new string whith the moved bbytes
 * 2 -> src : its a pointer which it shows in the memory direction which 
 is the string that you will be moving the bytes
 * 3 -> len : its the argument that shows you how meny bytes 
 you are going to move in memory.
 * meanwhile using this function we need to be sure that
  the byte that we are going to move from on place in memory 
  to another place do not overlap.
 * in comperison with the function memcpy() , this function its more 
 flexible and it reassuresthat we dont have overlaping inside the memory
 * in the beginig we need to declare 2 temporary pointers 
 for destination and source.
 * that we equal the temporary pointers with UNSIGNED CHARdst, and src..
 * then we declare a counter to kkep the count on the index inside src and dst.
 * then we check if the src and dest is overlapping // if in this case 
 * it overlaps when 
 * the dst its going to be bigger than the src..
 * then we loop length is greater than 0 // that means t
 * hat the move of bytes its going 
 * to happen from right to left (from the end)
 * inside while loop copy the source in to destination //
 * in the case that the src and dst its not overlapping
 * move the byte from src to dest
 * the return value is going to be the destination
 * */