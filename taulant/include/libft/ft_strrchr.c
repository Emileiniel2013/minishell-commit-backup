/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:37:08 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/23 19:23:52 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_c;

	last_c = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			last_c = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)s);
	}
	return ((char *)last_c);
}
/*this function it's similar to strchr(), but in
 * this case this function it finds the last pozicion of the
 * character that it is used on the string.
 * it takes the same argument :
 * 1-> *s --> its the string that we will search the character inside
 * 2 -> c --> this is the charactar that we are searching for
 * This function return a pointer that shows the last character used in
 * str or it will return NULL if we dont find any match.
 * */