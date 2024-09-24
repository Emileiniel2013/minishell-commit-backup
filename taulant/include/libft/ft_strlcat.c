/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:35:41 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/22 17:35:56 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>	

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_l;
	size_t	src_l;
	size_t	i;

	dest_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	if (dest_l >= dstsize)
		return (src_l + dstsize);
	i = -1;
	if (src_l < dstsize - dest_l)
	{
		while (++i < src_l + 1)
			dst[i + dest_l] = src[i];
	}
	else
	{
		while (++i < dstsize - dest_l - 1)
			dst[i + dest_l] = src[i];
		dst[dstsize - 1] = '\0';
	}
	return (dest_l + src_l);
}
/*
this function it serves to concatinate two strings together in meanwhile 
it saves the length of destionation to avoid the concatination beyond 
the limits of the memory
 * this function takes three arguments : 1-> dst: its the place in memory where 
 the characters from src are goint to be concatinate
 * 2 -> src: its the place in memory where we are going to take the characters 
 which later on we are going to concat with the dst
 * 3- dstsize : its the length which inside inclue all the 
 characters including the null terminate/
 * the first thing that we wwill do in this function is to find the length of 
 source and the length of the destionation
 *then we check if the dstsize its smaller or equal to the dst length and if 
 it's so we will return the length of src + dst
 * in other case we check if the dstsize its big enough for src and dst
 * inside we copy  to destination the source[len] + 1 character
 * if it is the other case arount that the dst size its big enough we will copy 
 * the elements from sorce until we reach dstsize - 1;
 * before the end we will add the null terminate to dst[dstsize -1];
 * the end we return the new length of the source concated with the destination;
 * */