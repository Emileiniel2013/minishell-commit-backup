/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:40:27 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/20 15:00:57 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	sub_s = (char *)malloc(len + 1);
	if (!sub_s)
		return (NULL);
	i = 0;
	while (len > i)
	{
		sub_s[i] = s[i + start];
		i++;
	}
	sub_s[i] = '\0';
	return ((char *)sub_s);
}
