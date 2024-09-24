/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:34:24 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/24 16:27:15 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*str;

	len = get_len(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = ft_calloc(sizeof(char), (len + 1));
	if (str == NULL)
		return (NULL);
	i = len - 1;
	if (n < 0)
	{
		str[0] = 45;
		n = -n;
	}
	while (n != 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}
/*
this function does the opposet if atoi // covet from int to ascii
in this function we have declared a function  that is used to get 
the len of the num. then we see for edge cases before alocatin memory,
then we set the sign of the number and after that this is 
the part when the conversion happens.
we devide the number by using modulo 10 and every sifer its going to be 
convertet on ascci value + 48 
*/