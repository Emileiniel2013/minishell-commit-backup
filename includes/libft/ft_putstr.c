/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:22:37 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/28 10:45:23 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	size_t	len;
	int		i;

	if (s == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	i = 0;
	len = 0;
	len = ft_strlen(s);
	while (len > 0)
	{
		i += ft_putchar(*s);
		len--;
		s++;
	}
	return (i);
}
