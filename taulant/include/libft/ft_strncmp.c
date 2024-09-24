/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:37:27 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/23 19:55:34 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1[0] && !s2[0])
		return (0);
	if (!s1[0])
		return (-1);
	if (!s2[0])
		return (1);
	while (s1[i] && s2[i] && n > i)
	{
		if ((char)s1[i] != (char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s1[i] != s2[i] && i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*this function is used to compere a set number of character inside 2 strings
the compare its based on a number that we set and it doesn't define the end of
the string.
this function takes three arguments :
1-> s1 and s2 =  are the strings that we compare
2-> n = its the number of the characters that we set to compare the value.
we return 0 if the strings have the same value
a negativ number when s1 character is less than s2 character.
a positive number when s1 character is bigger than s2 character.
first we set the edge cases for s1 and s2 
after we loop through our string until the number of the characters
that we have to compere. 
with the if condition we check if the character of s1 isn;t the same 
whith the character of s2. if the case its tru we will return the value converted
for each character according to alphabetic order.
*/