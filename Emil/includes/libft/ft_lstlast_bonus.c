/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:28:51 by temil-da          #+#    #+#             */
/*   Updated: 2024/04/14 19:35:02 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_bonus	*ft_lstlast(t_list_bonus *lst)
{
	int				a;
	t_list_bonus	*last;

	a = ft_lstsize(lst);
	while (a > 1)
	{
		lst = lst->next;
		a--;
	}
	last = lst;
	return (last);
}
