/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/23 17:08:57 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

bool    ft_isspace(char index)
{
    if (index == ' ')
        return (true);
    else
        return (false);
}

char    *ft_strndup(char *s1, size_t len)
{
 	size_t 	j;
	char	*cpy;

	j = 0;
	cpy = NULL;
	cpy = malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (s1[j] && j < len)
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

void	set_quote_type(int *quote_type, char quote)
{
	if (quote == '"')
		*quote_type = 2;
	else if (quote == '\'')
		*quote_type = 1;
}

token_type	identify_token(char *token, int quote_type)
{
	if (quote_type == 1)
		return (TOKEN_STRING);
	else if (quote_type == 2)
		return (TOKEN_DOUBLE_QUOTE);
	else if (ft_strncmp(token, "|", ft_strlen(token)) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strncmp(token, ">", ft_strlen(token)) == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(token, ">>", ft_strlen(token)) == 0)
		return (TOKEN_REDIRECT_OUT_APPEND);
	else if (ft_strncmp(token, "<<", ft_strlen(token)) == 0)
		return (TOKEN_HEREDOC);
	else
		return (TOKEN_STRING);
}

void	add_token_to_lst(t_tokens **list_head,char *content, token_type token)
{
	t_tokens			*new_token;
	t_tokens			*current;


	new_token = create_new_node(content, token);
	current = NULL;
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

t_tokens	*create_new_node(char *content, token_type token)
{
	t_tokens	*new_token;

	new_token = malloc(sizeof(t_tokens)); // TODO ERROR HANDLING
	new_token->content = ft_strdup(content);
	new_token->token = token;
	new_token->next = NULL;
	return (new_token);
}

void		free_token_lst(t_tokens *token_lst)
{
	t_tokens	*current;
	t_tokens	*next;

	current = token_lst;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}