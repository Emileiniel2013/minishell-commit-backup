/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:43:38 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/13 17:45:27 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
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
	ft_putchar_fd('\n', fd);
}
