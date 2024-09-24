/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:37:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/24 16:29:54 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*st;
	unsigned char	count;
	size_t			i;

	i = 0;
	st = (unsigned char *)s;
	count = (unsigned char)c;
	while (i < n)
	{
		if (st[i] == count)
			return ((void *) &st[i]);
		i++;
	}
	return (NULL);
}
/*
this function its the same as the strchr() but the only diff
is that in memchr() works with byte string (void *);
int main() 
{
    const char *str = "Hello, World!";
    char *ptr = (char *)ft_memchr(str, 'W', strlen(str));
    
    if (ptr != NULL) {
        printf("Found 'W' at position: %ld\n", ptr - str);
    } else {
        printf("Character 'W' not found.\n");
    }
    
    return 0;
}
*/