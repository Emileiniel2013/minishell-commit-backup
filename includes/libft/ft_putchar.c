/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:18:13 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/28 10:46:09 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	if (!*get_error())
	{
		if (write(1, &c, 1) == -1)
			set_error(1);
	}
	return (1);
}

int	*get_error(void)
{
	static int	error;

	return (&error);
}

void	set_error(int error)
{
	*get_error() = error;
}
