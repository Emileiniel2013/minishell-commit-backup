/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:41:30 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/05 14:01:47 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

/*
	lexer()
	t
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
			add_token(&head, current);
			i++;
		}
		else if (prompt[i] == '>' || prompt[i] == '<')
		{
			current = create_tok(create_redir_arr(prompt[i]), TOKEN_RIDIRECTION);
			add_token(&head, current);
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
			add_token(&head, current);
			free(buffer);
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