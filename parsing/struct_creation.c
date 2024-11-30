/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:16:25 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/26 15:49:26 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	add_token_to_table(t_table **table, t_tkn_lst *token_lst)
{
	t_table	*new_node;
	t_table	*current_node;
	t_tkn	token;

	new_node = NULL;
	current_node = NULL;
	token = token_lst->tkn;
	if (token == STRING || token == DOUBLE_QUOTE || token == SINGLE_QUOTE)
	{
		if (!(*table))
			allocate_table(table, false);
		current_node = *table;
		while (current_node->next)
			current_node = current_node->next;
		add_cmd_node(&current_node, token_lst->content);
	}
	else if (token_lst->tkn == PIPE)
	{
		current_node = *table;
		while (current_node->next)
			current_node = current_node->next;
		current_node->rightpipe = true;
		allocate_table(&new_node, true);
		current_node->next = new_node;
	}
}

void	allocate_table(t_table **table, bool leftpipe)
{
	*table = malloc(sizeof(t_table));
	if (!(*table))
		return ;
	if (leftpipe == true)
		(*table)->leftpipe = true;
	else
		(*table)->leftpipe = false;
	(*table)->rightpipe = false;
	(*table)->next = NULL;
	(*table)->command = NULL;
}

void	add_cmd_node(t_table **table, char *content)
{
	t_cmd	*new_node;
	t_cmd	*current_node;

	new_node = NULL;
	current_node = NULL;
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	if (!(*table)->command)
	{
		(*table)->command = new_node;
		(*table)->cmd_head = new_node;
	}
	else
	{
		current_node = (*table)->command;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
}

int	creat_close_file(t_mini *minish)
{
	int	fd;

	fd = -1;
	fd = open(minish->out_redir, O_CREAT, 0644);
	if (fd < 0)
		return (write_err(minish, 7, NULL), -1);
	close(fd);
	free(minish->out_redir);
	return (0);
}
