/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:32:31 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/18 11:37:35 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/* 
--> ft_isalnum -- alphabetical & numerical character  test
--> this function test for any charcter for in this case 
may be alphabetical Uper_case & Lower_case or a number charcter.
-->return value is non-zero value if the test is tru and finds
charter which it is alphabetical or numbers
returns zero if the test is false 
*/