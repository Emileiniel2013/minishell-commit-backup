/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pompt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:58 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/05 15:36:03 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

/*
	Here its where we start our shell loop//
	1->checking if the input comes wrom a interactiv terminal
	2-> the input its saved in prompt
*/

void prompt(t_msh *msh)
{
	char	*prompt;
	t_lexer *tokens;
	size_t i = 0;
	if (!isatty(STDIN_FILENO))
 		return ;
	while (1)
	{
		prompt = readline("Minishell~ ");
		if (prompt == NULL)
		{
			perror("Failed initializing prompt");
			break ;
		}
		if(ft_strncmp(prompt, "env", 4) == 0) // print the env 
		{
			while (msh->env[i])
			{
				printf("%s\n", msh->env[i]);
				i++;
			}
		}
		if(ft_strncmp(prompt, "exit", 4) == 0)
		{
			free(prompt); // free the exit part
			break;
		}
		if (*prompt)
			add_history(prompt);
		tokens = lexer(prompt);
		//free tokens
		if(tokens)
		{
			print_token(tokens);
			free_token(tokens);
		}
		
		free(prompt);
	}
}
