/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:01:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 20:50:53 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"
//Here are the helper functions for the token's

/*
	FUNTIONS that we need to recreate
	we need to create a token
	we need to look for special characters
	add token to te list of token
*/

int is_this(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/*
	this function creates a token 
	and sets the token type
*/

token_type get_token_type(char c)
{
	if (c == '|')
		return TOKEN_PIPE;
	if (c == '<' || c == '>')
		return TOKEN_RIDIRECTION;
	else
		return TOKEN_UNKNOWN;
}


t_token *create_tok(char *data, token_type type)
{
	t_token *token;

	token = malloc (sizeof(t_token));
	if (token == NULL)
	{
		perror("Malloc for tokens failed--->create_tok()\n");
		return NULL;
	}
	token->data = ft_strdup(data);
	token->type = type;
	token->next = NULL;
	return (token);
}

void add_token(t_token **tokens, t_token *new_token)
{
	t_token *temp;
	
	if(!*tokens)
		*tokens = new_token;
	else
	{
		temp = *tokens;
		while (temp->next)
		{
			temp = temp->next;
		}		
		temp->next = new_token;
	}
}

int ft_isspace(char c)
{
	return (c == ' ');
}

char *create_redir_arr(char c)
{
	char *arr;

	arr = malloc(2 * sizeof(char));
	if (!arr)
	{
		perror("malloc of red_arr failed->> create_red_arr[]");
		return NULL;
	}
	arr[0] = c;
	arr[1] = '\0';
	return arr;
}

void print_token(t_token *tokens)
{
	
	while (tokens)
	{
		printf("Token : %s\n" , tokens->data);
		tokens = tokens->next;
			
	}
}