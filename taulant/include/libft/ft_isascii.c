/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:33:01 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/18 11:40:07 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int a)
{
	if (a >= 0 && a <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*
ft_isascii -- test for ASCII characters
this function test for ASCII characters between 0 to 127(decimal)
this function return a non-zero value if the test is tru (if it is ascii char)
return 0 if the test is false
*/