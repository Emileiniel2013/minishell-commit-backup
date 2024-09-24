/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:34:06 by tndreka           #+#    #+#             */
/*   Updated: 2024/03/22 17:27:21 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = b;
	while (len > 0)
	{
		*temp = (unsigned char)c;
		temp++;
		len--;
	}
	return (b);
}

/*this function its udsed to set a vaule on a memory place
 * this function takes 3 arguments , 1-> the pointer is 
 the place on memory that you will aply the memset function
 * 2-> the c is the new value that we are setting on the memory place
 * 3->the len is for how many bytes we are setting 
 * the value  C on the memory place
 * implementation : the first step is to declere a temporary CHAR  pointer 
 * that will be equal to our VOID pointer
 * we are going to loop in the pointer until we reach 0 length 
 * // that means until we dont have anymore values to set in the string//
 * inside the while loop is where  the memset is created and here we we 
 * tell that on  temporary pointer is going to set 
 * the values off C convertet as unsigned char
 * then we will increment the pointer so it will 
 * go on to next memory byte to set the value of c
 * and decrent the length until 0 because we start the while 
 * loop as (len > 0) => this means that from the argument we get for 
 * how men bytes we will fill the pointer until we dont have anymore to fill.//
  */