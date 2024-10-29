/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/29 12:41:18 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_tkn_lst	*process_input(char *line, t_mini *mini)
{
	t_tkn_lst	*token_lst_head;
	char		*content;
	int			quote_type;
	t_token		type;

	token_lst_head = NULL;
	quote_type = 0;
	content = get_next_token(line, &quote_type, mini);
	while (content != NULL)
	{
		if (content[0] == '\0')
		{
			free_token_lst(token_lst_head);
			return (NULL);
		}
		type = identify_token(content, quote_type);
		add_tkn_to_lst(&token_lst_head, content, type);
		free(content);
		content = get_next_token(line, &quote_type, mini);
	}
	return (token_lst_head);
}

char	*get_next_token(char *line, int *quote_type, t_mini *mini)
{
	static int	index = 0;
	int			start;
	char		*token;

	start = index;
	token = NULL;
	while (line[index] && ft_isspace(line[index]))
		index++;
	if (line[index] == '"' || line[index] == '\'')
		token = handle_quote(mini, quote_type, &index, line);
	else
	{
		start = index;
		while (line[index] && !ft_isspace(line[index]))
			index++;
		if (index > start)
			token = ft_strndup(line + start, index - start);
		else
			index = 0;
	}
	return (token);
}

char	*handle_quote(t_mini *mini, int *quote_type, int *index, char *line)
{
	char	quote;
	int		start;
	char	*token;

	set_q_type(quote_type, line[*index]);
	quote = line[(*index)++];
	start = *index;
	token = NULL;
	while (line[*index] && line[*index] != quote)
		(*index)++;
	if (line[*index] == quote)
	{
		token = ft_strndup(line + start, (*index) - start);
		(*index)++;
		return (token);
	}
	else
	{
		write_err(mini, 16);
		*index = 0;
		return ("\0");
	}
}

void	add_tkn_to_lst(t_tkn_lst **list_head, char *content, t_token token)
{
	t_tkn_lst	*new_token;
	t_tkn_lst	*current;

	current = NULL;
	new_token = create_new_node(content, token);
	if (!new_token)
		return ;
	if (*list_head == NULL)
		*list_head = new_token;
	else
	{
		current = *list_head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}
