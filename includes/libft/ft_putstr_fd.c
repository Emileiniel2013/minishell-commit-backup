/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:21:24 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/13 17:35:35 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	len = ft_strlen(s);
	while (len > 0)
	{
		ft_putchar_fd(*s, fd);
		len--;
		s++;
	}
}
