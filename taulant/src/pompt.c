/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pompt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:58 by tndreka           #+#    #+#             */
/*   Updated: 2024/09/24 21:15:58 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

void prompt(t_msh *msh)
{
	char	*prompt;
	size_t i = 0;
	if (!isatty(STDIN_FILENO))
 		return ;
	while (1)
	{
		prompt = readline("Minishell~ ");
		if (prompt == NULL)
			break ;
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
		free(prompt);
	}
}
