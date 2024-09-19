/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:58:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/28 10:53:53 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(void *n);
static void	ft_convert_numbers(void *n, char *str, int digits);

char	*ft_itoa_ptr(void *n)
{
	char	*str;
	int		digits;

	digits = 0;
	digits = ft_count_digits(n);
	str = malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (set_error(1), NULL);
	if (n == NULL)
	{
		str[0] = '0';
		str[1] = 'x';
		str[2] = '0';
		str[3] = '\0';
		return (str);
	}
	ft_convert_numbers(n, str, digits);
	str[0] = '0';
	str[1] = 'x';
	str[digits] = '\0';
	return (str);
}

static int	ft_count_digits(void *n)
{
	int		count;
	size_t	ptr;

	ptr = (size_t)n;
	if (n == NULL)
		return (3);
	count = 0;
	if (ptr == 0)
		return (2);
	while (ptr != 0)
	{
		count++;
		ptr /= 16;
	}
	return (count + 2);
}

static void	ft_convert_numbers(void *n, char *str, int digits)
{
	int		a;
	char	*base16;
	size_t	ptr;

	ptr = (size_t)n;
	base16 = "0123456789abcdef";
	a = 0;
	if (ptr == 0)
	{
		str[a] = '0';
		return ;
	}
	while (digits-- > 0 && ptr >= 16)
	{
		str[digits] = base16[ptr % 16];
		ptr = ptr / 16;
	}
	str[digits] = base16[ptr % 16];
}
