/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:41:30 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 18:15:24 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

/*
	lexer()
	this function loops through the input from 
	readlibe(), and 
*/

t_token *lexer(char *prompt)
{
	char *buffer;
	t_token *head = NULL;
	t_token *current = NULL;
	size_t len = 0;
	int i = 0;

	while (prompt[i])
	{
		while (prompt[i] && ft_isspace(prompt[i]))
			i++;
		if(prompt[i] == '|')
		{
			current = create_tok("|", TOKEN_PIPE);
			i++;
		}
		else if (prompt[i] == '>' || prompt[i] == '<')
		{
			current = create_tok(create_redir_arr(prompt[i]), TOKEN_RIDIRECTION);
			i++;
		}
		else if (prompt[i])
		{
			len = 0;
			while (prompt[i] && !ft_isspace(prompt[i]) && prompt[i] != '|' && prompt[i] != '<' && prompt[i] != '<')
			{
				len++;
				i++;
			}
			buffer = malloc((len + 1) * sizeof(char));
			if(!buffer)
			{
				perror("malloc for buffer at lexer() FAILED !!");
				return NULL;
			
			}
			ft_strncpy(buffer, prompt + (i - len) , len);
			buffer[len] = '\0';
			current = create_tok(buffer, TOKEN_WORD);
			free(buffer);
		}
		if (current)
		{
			current->next = head;
			head = current;
		}
	}
	return head;	
}

void free_token(t_token *head)
{
	t_token *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->data);
		free(tmp);
	}
}