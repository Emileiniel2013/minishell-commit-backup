/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:17:27 by temil-da          #+#    #+#             */
/*   Updated: 2024/04/14 19:35:35 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_bonus	*ft_lstnew(void *content)
{
	t_list_bonus	*node;

	node = malloc(sizeof(t_list_bonus));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
