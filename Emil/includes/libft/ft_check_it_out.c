/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_it_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:00:18 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/28 10:51:37 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_it_out(char c, va_list ap)
{
	int		count;
	char	*bro;

	bro = NULL;
	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (c == 'd' || c == 'i')
		bro = (ft_itoa_printf(va_arg(ap, int)));
	else if (c == 'u')
		bro = (ft_itoa_u(va_arg(ap, unsigned int)));
	else if (c == '%')
		count += ft_putchar('%');
	else if (c == 'x' || c == 'X')
		bro = (ft_itoa_hex((va_arg(ap, unsigned int))));
	if (c == 'X' && bro)
		ft_toupper_printf(bro);
	else if (c == 'p')
		bro = ft_itoa_ptr(va_arg(ap, void *));
	count += print_my(bro);
	free_my(bro);
	return (count);
}
