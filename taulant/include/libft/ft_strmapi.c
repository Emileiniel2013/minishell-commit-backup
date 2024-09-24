/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:39:21 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/19 18:33:31 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*rs;
	unsigned int	i;

	rs = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!rs)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s))
		rs[i] = (*f)(i, s[i]);
	rs[i] = 0;
	return (rs);
}
