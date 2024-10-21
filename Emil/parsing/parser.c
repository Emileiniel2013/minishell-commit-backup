/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/21 17:14:28 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	parse_input(char *line, t_minishell *minishell)
{
	t_tokens		*token_lst;
	t_command_table	*table;
	int				i;

	i = 0;
	table = NULL;
	token_lst = process_input(line, minishell);
	if (token_lst == NULL)
		return ;
	while (token_lst)
	{
		if (token_lst->token == TOKEN_REDIRECT_OUT || token_lst->token == TOKEN_REDIRECT_OUT_APPEND || token_lst->token == TOKEN_REDIRECT_IN)
		{
			if (check_valid_redir_input(&token_lst, minishell) == -1)
				break ; // FREE EVERYTHING, GO BACK TO 0
		}
		if (token_lst->token == TOKEN_STRING || token_lst->token == TOKEN_DOUBLE_QUOTE)
			expand_env_vars(&token_lst->content, minishell, token_lst->token);
		if (token_lst->token == TOKEN_HEREDOC)
		{
			if (handle_heredoc(&token_lst, minishell) == -1)
				break ; // FREE EVERYTHING, GO BACK TO 0
		}	
		if (token_lst->token == TOKEN_PIPE)
		{
			if (check_valid_pipe(token_lst, table, minishell) == -1)
				break ; // FREE EVERYTHING, GO BACK TO 0
		}
		if (token_lst->token != TOKEN_FILENAME | token_lst->token != TOKEN_DELIMITER)
			add_token_to_table(&table, token_lst);
		token_lst = token_lst->next;
	}
	minishell->table = table;
}
