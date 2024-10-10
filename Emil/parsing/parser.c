/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/08 13:00:30 by temil-da         ###   ########.fr       */
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
	token_lst = process_input(line);
	while (token_lst != NULL)
	{
		if (token_lst->token == TOKEN_STRING || token_lst->token == TOKEN_DOUBLE_QUOTE)
			expand_env_vars(&token_lst->content, minishell, token_lst->token);
		token_lst = token_lst->next;
	}
	
}