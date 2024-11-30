/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:42:30 by temil-da          #+#    #+#             */
/*   Updated: 2024/04/14 19:25:29 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	char	*a;

	if (s == NULL)
		return (NULL);
	a = (char *)s;
	while (*a != '\0')
	{
		if (*a == (unsigned char)c)
			return (a);
		a++;
	}
	if (*a == (unsigned char)c)
		return (a);
	return (NULL);
}

int	ft_strlen_gnl(const char *s)
{
	int	a;

	a = 0;
	while (*s && *s != '\n')
	{
		s++;
		a++;
	}
	if (*s == '\n')
		a++;
	return (a);
}

char	*ft_strcat_gnl(char *dest, const char *src)
{
	char	*x;
	int		a;
	int		b;

	a = 0;
	b = 0;
	x = NULL;
	x = dest;
	while (x[a] != '\0')
		a++;
	while (src[b] != '\0')
	{
		x[a] = src[b];
		if (x[a] == '\n')
		{
			a++;
			break ;
		}
		b++;
		a++;
	}
	x[a] = '\0';
	return (x);
}

void	free_nodes(t_list *head, t_list *last_node)
{
	t_list	*current;
	t_list	*next;

	current = head;
	if (current == NULL)
		return ;
	if (last_node == NULL)
	{
		while (current->next != NULL)
			current = current->next;
		last_node = current;
	}
	current = head;
	while (current != NULL && current != last_node)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	if (current == last_node)
	{
		free(current->content);
		free(current);
	}
}

t_list	*ft_find_last_node_nl(t_list *node)
{
	while (node->next != NULL)
	{
		if (ft_strchr_gnl(node->content, '\n') != NULL)
			break ;
		node = node->next;
	}
	return (node);
}
