/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:45:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/30 15:05:10 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

bool	ft_isspace(char index)
{
	if (index == ' ')
		return (true);
	else
		return (false);
}

void	free_tkn_lst(t_tkn_lst *token_lst)
{
	t_tkn_lst	*current;
	t_tkn_lst	*next;

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

char	*ft_strndup(char *s1, size_t len)
{
	size_t	j;
	char	*cpy;

	j = 0;
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

t_tkn_lst	*create_new_node(char *content, t_tkn token)
{
	t_tkn_lst	*new_token;

	new_token = malloc(sizeof(t_tkn_lst));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	new_token->tkn = token;
	new_token->next = NULL;
	return (new_token);
}

void	write_err(t_mini *minish, int code, char *arg)
{
	if (!arg)
	{
		if (code == 16)
		{
			write(STDERR_FILENO, "Minishell: synthax error: u", 27);
			write(STDERR_FILENO, "nmatched quote character\n", 26);
		}
		else if (code == 8 || code == 13 || code == 10)
		{
			write(STDERR_FILENO, "Minishell: syntax error near ", 29);
			write(STDERR_FILENO, "unexpected token `newline'\n", 28);
		}
		else if (code == 15)
			write(STDERR_FILENO, "Minishell: Failed to create heredoc file\n", 42);
	}
	else
	{
		if (code == 9 || code == 14 || code == 11 || code == 12)
		{
			write(STDERR_FILENO, "Minishell: syntax error ", 24);
			write(STDERR_FILENO, "near unexpected token `", 23);
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, "'\n", 2);
		}
	}
	minish->exit_code = code;
	minish->success = false;
}
