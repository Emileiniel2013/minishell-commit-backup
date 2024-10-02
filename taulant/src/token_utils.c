/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:01:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/02 18:19:14 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mini_sh.h"

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
