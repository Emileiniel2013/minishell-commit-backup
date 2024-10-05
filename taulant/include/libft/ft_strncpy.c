/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:28:04 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 18:09:33 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	i = 0;
	if (dst == NULL || src == NULL || n == 0)
		return (dst);
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);	
}

// int main()
// {
// 	char string[] = "abcdef";
// 	char buff[20];
// 	for (size_t i = 0; i < 10; i++)
// 	{
// 		buff[i] = '#';
// 	}
// 	ft_strncpy(buff, string, 3);
// 	printf("buff: %s\n", buff);
// 	return 0;
// }