/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:58:24 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/28 10:55:26 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(unsigned long n);
static void	ft_convert_numbers(unsigned long n, char *str, int digits);

char	*ft_itoa_hex(unsigned long n)
{
	char	*str;
	int		digits;

	digits = 0;
	digits = ft_count_digits(n);
	str = malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (set_error(1), NULL);
	ft_convert_numbers(n, str, digits);
	str[digits] = '\0';
	return (str);
}

static int	ft_count_digits(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static void	ft_convert_numbers(unsigned long n, char *str, int digits)
{
	int		a;
	char	*base16;

	base16 = "0123456789abcdef";
	a = 0;
	if (n == 0)
	{
		str[a] = '0';
		return ;
	}
	while (digits-- > 0 && n >= 16)
	{
		str[digits] = base16[n % 16];
		n = n / 16;
	}
	str[digits] = base16[n % 16];
}
