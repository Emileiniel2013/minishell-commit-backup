/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:36:36 by tndreka           #+#    #+#             */
/*   Updated: 2024/04/25 00:17:29 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

/*this function is used in C to find the first pozicion to acharacter
 * that we set in a string. this function accept 2 argument :
 * 1 -> *s = is the string that we are going to search inside for the
 * character first position tha we wont to find.
 * 2 -> c = its the character that we are searching.
 * this function it will return a pointer that shows the first character
 * that we have find inside of the s or its going to return NULL if we didn't
 * find the character/
 * */