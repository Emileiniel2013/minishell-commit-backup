/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:48:45 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/11 12:30:09 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	size_t	a;
	void	*ptr;

	total_size = count * size;
	ptr = malloc(total_size);
	a = 0;
	if (ptr != NULL)
	{
		while (a < total_size)
		{
			((char *)ptr)[a] = 0;
			a++;
		}
	}
	return (ptr);
}
