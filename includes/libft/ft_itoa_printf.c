/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:59:44 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/28 10:54:28 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n);
static void	ft_convert_numbers(int n, char *str, int digits);

char	*ft_itoa_printf(int n)
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

static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		return (11);
	}
	if (n < 0)
	{
		n = -n;
		count++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_convert_numbers(int n, char *str, int digits)
{
	int	a;

	a = 0;
	if (n == 0)
	{
		str[a] = '0';
		return ;
	}
	if (n == -2147483648)
	{
		str[a++] = '-';
		str[a++] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		str[a] = '-';
		n = -n;
	}
	while (digits-- > 0 && n > 9)
	{
		str[digits] = (n % 10) + '0';
		n = n / 10;
	}
	str[digits] = (n % 10) + '0';
}
