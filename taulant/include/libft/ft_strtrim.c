/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:40:18 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/18 13:58:22 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	size_t	start;
	size_t	new_len;
	char	*new_str;

	len = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (len > start && ft_strchr(set, s1[len - 1]))
		len--;
	new_len = len - start;
	new_str = (char *)ft_calloc((new_len + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1 + start, new_len);
	return (new_str);
}
