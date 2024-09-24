/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:33:21 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/18 11:42:42 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int p)
{
	if (p >= 32 && p <= 126)
	{
		return (p);
	}
	else
	{
		return (0);
	}
}

/*
ft_isprint--printing character test(including space " ")
this function test for any printin characters including space between the
values 32(space) until 126.
if the stest is tru it return a non-zero value
if the test is false return 0. 
*/