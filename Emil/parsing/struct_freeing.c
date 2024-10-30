/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_freeing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:14:33 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/30 18:02:13 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	free_table(t_mini *minish)
{
	t_table	*current;
	t_table	*next;

	next = NULL;
	current = minish->table_head;
	while (current)
	{
		next = current->next;
		if (current->cmd_head)
			free_cmd(current->cmd_head);
		free(current);
		current = next;
	}
	minish->table = NULL;
	minish->table_head = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

void	free_parser(t_mini *minish, t_tkn_lst *lst, t_table *table)
{
	free_tkn_lst(lst);
	if (table)
	{
		minish->table_head = table;
		free_table(minish);
	}
}
