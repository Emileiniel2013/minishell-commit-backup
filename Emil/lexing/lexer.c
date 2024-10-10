/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/07 13:49:19 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

char    *get_next_token(char *line, int *quote_type)
{
    static int	index = 0;
	int			start;
    char		*token;
	char		quote;
	
	start = index;
	token = NULL;
	quote = '\0';
	*quote_type = 0;
    while(line[index] && ft_isspace(line[index]))
		index++;
	if (line[index] == '"' || line[index] == '\'')
	{
		set_quote_type(quote_type, line[index]);
		quote = line[index++];
		start = index;
		while (line[index] && line[index] != quote)
			index++;
		if (line[index] == quote)
		{
			token = ft_strndup(line + start, index - start);
			index++;
		}
		else
		{
			printf("Synthax error: unmatched quote character\n");
			index = 0;
			return (NULL); // TODO: ERROR HANDLING
		}
	}
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



t_tokens	*process_input(char *line)
{
    t_tokens    *token_lst_head;
    char        *content;
	int			quote_type;
	token_type	type;

	token_lst_head = NULL;
	quote_type = 0;
	content = get_next_token(line, &quote_type);
	while (content != NULL)
	{
		type = identify_token(content, quote_type);
		add_token_to_lst(&token_lst_head, content, type);
		free(content);
		content = get_next_token(line, &quote_type);
	}
	return(token_lst_head);
}
