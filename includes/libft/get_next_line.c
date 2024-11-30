/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:37:35 by temil-da          #+#    #+#             */
/*   Updated: 2024/04/14 19:29:29 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	clean_nodes(t_list **head, int x, int z)
{
	t_list	*new_head;
	t_list	*last_node;
	char	*temp;

	last_node = *head;
	new_head = NULL;
	last_node = ft_find_last_node_nl(*head);
	while (last_node->content[x] != '\n' && last_node->content[x] != '\0')
		++x;
	if (last_node->content[x] == '\0')
		return (free_nodes(*head, last_node), *head = NULL, 0);
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (1);
	while (last_node->content[x] != '\0' && last_node->content[++x])
		temp[z++] = last_node->content[x];
	temp[z] = '\0';
	if (ft_create_node(&new_head, &temp) == 0)
		return (free(temp), 1);
	if (last_node->next == NULL)
		new_head->next = NULL;
	else
		new_head->next = last_node->next;
	return (free_nodes(*head, last_node), *head = new_head, 0);
}

char	*ft_write_line(t_list *head)
{
	int		i;
	t_list	*current_node;
	char	*line;

	current_node = head;
	while (current_node != NULL)
	{
		i = i + ft_strlen_gnl(current_node->content);
		if (ft_strchr_gnl(current_node->content, '\n') != NULL)
			break ;
		current_node = current_node->next;
	}
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[0] = '\0';
	current_node = head;
	while (current_node != NULL)
	{
		ft_strcat_gnl(line, current_node->content);
		if (ft_strchr_gnl(current_node->content, '\n'))
			break ;
		current_node = current_node->next;
	}
	return (line);
}

int	ft_create_node(t_list **head, char **buffer)
{
	t_list	*current_node;
	t_list	*new_node;

	current_node = *head;
	new_node = NULL;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = *buffer;
	new_node->next = NULL;
	if (!current_node)
		*head = new_node;
	else
	{
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	return (1);
}

int	ft_fetch_line(t_list **head, int fd)
{
	int		i;
	char	*buffer;

	buffer = NULL;
	i = 0;
	while ((ft_strchr_gnl(buffer, '\n') == NULL))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (-1);
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			return (free(buffer), i);
		buffer[i] = '\0';
		if (ft_create_node(head, &buffer) == 0)
		{
			free (buffer);
			return (-1);
		}
	}
	return (i);
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*line;
	int				i;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
	{
		if (head != NULL)
		{
			free_nodes(head, NULL);
			head = NULL;
		}
		return (NULL);
	}
	i = ft_fetch_line(&head, fd);
	if (head == NULL || (head == NULL && i == 0) || i == -1)
		return (free_nodes(head, NULL), NULL);
	line = ft_write_line(head);
	if (line == NULL)
		return (free_nodes(head, NULL), NULL);
	if (clean_nodes(&head, 0, 0) == 1)
		return (free_nodes(head, NULL), NULL);
	if (ft_strlen_gnl(line) == 0)
		return (free(line), NULL);
	return (line);
}
