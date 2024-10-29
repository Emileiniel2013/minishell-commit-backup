/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:45:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/28 20:21:49 by temil-da         ###   ########.fr       */
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

void	free_token_lst(t_tkn_lst*token_lst)
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

t_tkn_lst	*create_new_node(char *content, t_token token)
{
	t_tkn_lst	*new_token;

	new_token = malloc(sizeof(t_tkn_lst));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	new_token->token = token;
	new_token->next = NULL;
	return (new_token);
}

void	write_err(t_mini *mini, int err_code)
{
	if (err_code == 16)
	{
		write(STDERR_FILENO, "Minishell: synthax error: u", 27);
		write(STDERR_FILENO, "nmatched quote character\n", 26);
		mini->exit_code = 16;
		mini->success = false;
	}
}
