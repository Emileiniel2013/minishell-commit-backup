/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pompt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:58 by tndreka           #+#    #+#             */
/*   Updated: 2024/09/20 16:56:38 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

int prompt(char *env_copy)
{
	char	*prompt;
	if (!isatty(STDIN_FILENO))
 		return(EXIT_FAILURE);
	prompt = readline("Minishell~ ");
	while (*prompt)
	{
		if(strcmp(prompt, "env"))
		{
			printf("print enviroment \n%s\n ", env_copy);
		}
		prompt++;
	}
	
	printf("%s\n", prompt);
	return(EXIT_SUCCESS);
}
