/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:19:35 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/28 10:49:46 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	set_error(0);
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
			count += ft_check_it_out(*++str, ap);
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(ap);
	if (*get_error())
		return (-1);
	return (count);
}
