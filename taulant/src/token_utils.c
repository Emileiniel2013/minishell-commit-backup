/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:01:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/05 15:46:19 by tndreka          ###   ########.fr       */
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

t_token get_token_type(char c)
{
	if (c == '|')
		return TOKEN_PIPE;
	else if (c == '<')
		return TOKEN_RIDIRECTION_LESS;
	else if (c == '>')
		return TOKEN_RIDIRECTION_GREAT;
	else if (ft_strncmp(&c, "<<", 2) == 0)
		return TOKEN_RIDIRECTION_LESS_LESS;
	else if (ft_strncmp(&c, ">>", 2) == 0)
		return TOKEN_RIDIRECTION_GREAT_GREAT;
	else
		return TOKEN_UNKNOWN;
}


t_lexer *create_tok(char *data, t_token type)
{
	t_lexer *token;

	token = malloc (sizeof(t_lexer));
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

void add_token(t_lexer **tokens, t_lexer *new_token)
{
	t_lexer *temp;
	
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

void print_token(t_lexer *tokens)
{
	char *str;
	//printf("ERROR HERE\n");
	while (tokens)
	{
		//printf("ERROR HERE1\n");
		if (tokens->type == TOKEN_WORD)
		{
			//printf("ERROR HERE2\n");
			str = "WORD";
		}
		else if (tokens->type == TOKEN_PIPE)
		{
			//printf("ERROR HERE3\n");
			str = "PIPE";
		}
		else if (tokens->type == TOKEN_RIDIRECTION_LESS)
		{
			//printf("ERROR HERE4\n");
			str = "RIDIRECTION_LESS";
		}
		else if (tokens->type == TOKEN_RIDIRECTION_GREAT)
		{
			//printf("ERROR HERE4\n");
			str = "RIDIRECTION_GREAT";
		}
		else if (tokens->type == TOKEN_RIDIRECTION_LESS_LESS)
		{
			//printf("ERROR HERE4\n");
			str = "RIDIRECTION_LESS_LESS";
		}
		else if (tokens->type == TOKEN_RIDIRECTION_GREAT_GREAT)
		{
			//printf("ERROR HERE4\n");
			str = "RIDIRECTION_GREAT_GREAT";
		}
		else
		{
			//printf("ERROR HERE5\n");
			str = "UNKNOWN";
		}
		//printf("ERROR HERE666\n");
		printf("Token : %s  Type: %s\n" , tokens->data, str);
		tokens = tokens->next;
	}
}