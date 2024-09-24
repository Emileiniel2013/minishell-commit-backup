/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:39:09 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/24 16:15:34 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}
/*this functio converts a string to int like from the name from "ASCII" to
Intiger.
in this function in the begging we see for spaces & other character that we may 
have in the start of string .
the second step is to set the sign of the number + or -;
the most imoprtant part this is when the conversion happens inside the while loop
for each character to number unsing the values from ascii table
for every character from 0 to 9, the value its added to ending result by 
multipplying with 10 and by adding the actual n;
*/