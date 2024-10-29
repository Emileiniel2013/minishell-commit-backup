/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/29 12:33:24 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	parse_input(char *line, t_mini *minishell)
{
	t_tkn_lst	*token_lst;
	t_tkn_lst	*lst_head;
	t_table		*table;

	table = NULL;
	if (line[0] != '\0')
		add_history(line);
	token_lst = process_input(line, minishell);
	lst_head = token_lst;
	if (!token_lst)
		return ;
	while (token_lst)
	{
		// printf("%s\n", print_token(token_lst->token));
		if (token_lst->token == REDIRECT_OUT || token_lst->token == REDIRECT_OUT_APPEND || token_lst->token == REDIRECT_IN)
		{
			if (check_valid_redir_input(&token_lst, minishell) == -1)
			{
				free_token_lst(lst_head);
				if (table)
				{
					minishell->table_head = table;
					free_table(minishell);
				}
				return ;
			}
		}
		if (token_lst->token == STRING || token_lst->token == DOUBLE_QUOTE)
			expand_env_vars(&token_lst->content, minishell);
		if (token_lst->token == HEREDOC)
		{
			if (handle_heredoc(&token_lst, minishell) == -1)
			{
				free_token_lst(lst_head);
				if (table)
				{
					minishell->table_head = table;
					free_table(minishell);
				}
				return ;
			}
		}	
		if (token_lst->token == PIPE)
		{
			if (check_valid_pipe(token_lst, table, minishell) == -1)
			{
				free_token_lst(lst_head);
				if (table)
				{
					minishell->table_head = table;
					free_table(minishell);
				}
				return ;
			}
		}
		if ((token_lst->token != FILENAME) | (token_lst->token != DELIMITER))
			add_token_to_table(&table, token_lst);
		token_lst = token_lst->next;
	}
	free_token_lst(lst_head);
	minishell->table = table;
	minishell->table_head = table;
}
