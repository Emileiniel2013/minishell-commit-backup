/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/19 16:17:45 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/executor.h"

void	executor(command_table *table)
{
	if (ft_strncmp(table->simple_command->content, "echo", 4) == 0)
		handle_echo(table->simple_command->next);
	if (ft_strncmp(table->simple_command->content, "pwd", 3) == 0)
		handle_pwd(table);
	if (ft_strncmp(table->simple_command->content, "cd", 2) == 0)
 		handle_cd(table);
}

char	**copy_env(char **envp)
{
	char	**cpy;
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char *) * i);
	i = 0;
	while (envp[i] != NULL)
	{
		size = ft_strlen(envp[i]);
		cpy[i] = malloc(sizeof(char) * size + 1);
		ft_strlcpy(cpy[i], envp[i], size + 1);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}


int	main(int argc, char *argv[], char *envp[])
{
	command_table		*table;
	t_command			*command_head;
	t_command			*next_command;
	// t_command			*current_command;
	char				**envp_cpy;
	int					i;
	(void)argv;
	(void)argc;
	
	i = 0;
	envp_cpy = copy_env(envp);
	table = malloc(sizeof(command_table));
	table->envp = envp_cpy;
	table->leftpipe = false;
	table->rightpipe = false;
	table->next = NULL;
	
	// echo TEST 
	// command_head = malloc(sizeof(t_command));
	// table->simple_command = command_head;
	// command_head->content = malloc(sizeof(char) * 5);
	// ft_strlcpy(command_head->content, "echo", 5);
	// command_head->token = TOKEN_COMMAND;
	
	// next_command = malloc(sizeof(t_command));
	// next_command->content = malloc(sizeof(char) * 6);
	// ft_strlcpy(next_command->content, "Hello", 6);
	// next_command->token = TOKEN_LITERAL;
	// next_command->next = NULL;
	// command_head->next = next_command;

	// current_command = next_command;
	// next_command = malloc(sizeof(t_command));
	// next_command->content = malloc(sizeof(char) * 6);
	// ft_strlcpy(next_command->content, "World", 6);
	// next_command->next = NULL;
	// next_command->token = TOKEN_LITERAL;
	// current_command->next = next_command;

	// pwd TEST
	// command_head = malloc(sizeof(t_command));
	// table->simple_command = command_head;
	// command_head->content = malloc(sizeof(char) * 4);
	// ft_strlcpy(command_head->content, "pwd", 4);
	// command_head->token = TOKEN_COMMAND;

	// cd TEST 
	command_head = malloc(sizeof(t_command));
	table->simple_command = command_head;
	command_head->content = malloc(sizeof(char) * 3);
	ft_strlcpy(command_head->content, "cd", 3);
	command_head->token = TOKEN_COMMAND;

	next_command = malloc(sizeof(t_command));
	next_command->content = malloc(sizeof(char) * 44);
	ft_strlcpy(next_command->content, "/Users/temil-da/Documents/Minishell2/Test6", 44);
	next_command->token = TOKEN_LITERAL;
	next_command->next = NULL;
	command_head->next = next_command;

	executor(table);
	return (0);
}