/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/24 15:51:04 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/executor.h"

void	executor(t_minishell *minishell)
{
	while (minishell->table != NULL)
	{
		if (ft_strncmp(minishell->table->simple_command->content, "echo", 4) == 0)
			handle_echo(minishell->table->simple_command->next);
		else if (ft_strncmp(minishell->table->simple_command->content, "pwd", 3) == 0)
			handle_pwd(minishell);
		else if (ft_strncmp(minishell->table->simple_command->content, "cd", 2) == 0)
			handle_cd(minishell);
		else if (ft_strncmp(minishell->table->simple_command->content, "env", 3) == 0)
			handle_env(minishell);
		else if (ft_strncmp(minishell->table->simple_command->content, "export", 6) == 0)
			handle_export(minishell);
		else if (ft_strncmp(minishell->table->simple_command->content, "unset", 5) == 0)
			handle_unset(minishell);
		else
			check_path(minishell);
		minishell->table = minishell->table->next;
	}
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
	t_minishell			*minishell;
	command_table		*table;
	// command_table		*table_2;
	t_command			*command_head;
	// t_command			*next_command;
	// t_command			*command_head_2;
	// t_command			*next_command_2;
	// t_command			*current_command;
	char				**envp_cpy;
	int					i;
	(void)argv;
	(void)argc;
	
	i = 0;
	minishell = malloc(sizeof(t_minishell));
	envp_cpy = copy_env(envp);
	minishell->env = envp_cpy;
	table = malloc(sizeof(command_table));
	minishell->table = table;
	// table_2 = malloc(sizeof(command_table));
	table->leftpipe = false;
	table->rightpipe = false;
	table->next = NULL;
	// table_2->leftpipe = false;
	// table_2->rightpipe = false;
	// table_2->next = NULL;
	
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
	// command_head = malloc(sizeof(t_command));
	// table->simple_command = command_head;
	// command_head->content = malloc(sizeof(char) * 3);
	// ft_strlcpy(command_head->content, "cd", 3);
	// command_head->token = TOKEN_COMMAND;

	// next_command = malloc(sizeof(t_command));
	// next_command->content = malloc(sizeof(char) * 44);
	// ft_strlcpy(next_command->content, "../Minishel", 44);
	// next_command->token = TOKEN_LITERAL;
	// next_command->next = NULL;
	// command_head->next = next_command;

	// env TEST 
	// command_head = malloc(sizeof(t_command));
	// table->simple_command = command_head;
	// command_head->content = malloc(sizeof(char) * 4);
	// ft_strlcpy(command_head->content, "env", 4);
	// command_head->token = TOKEN_COMMAND;

	// export TEST 
	// command_head = malloc(sizeof(t_command));
	// table->simple_command = command_head;
	// command_head->content = malloc(sizeof(char) * 7);
	// ft_strlcpy(command_head->content, "export", 7);
	// command_head->token = TOKEN_COMMAND;

	// next_command = malloc(sizeof(t_command));
	// next_command->content = malloc(sizeof(char) * 22);
	// ft_strlcpy(next_command->content, "TEST_VAR=Hello, world", 22);
	// next_command->token = TOKEN_LITERAL;
	// next_command->next = NULL;
	// command_head->next = next_command;

	//unset TEST
	// command_head_2 = malloc(sizeof(t_command));
	// table_2->simple_command = command_head_2;
	// command_head_2->content = malloc(sizeof(char) * 6);
	// ft_strlcpy(command_head_2->content, "unset", 6);
	// command_head_2->token = TOKEN_COMMAND;

	// next_command_2 = malloc(sizeof(t_command));
	// next_command_2->content = malloc(sizeof(char) * 10);
	// ft_strlcpy(next_command_2->content, "TEST_VAR=", 10);
	// next_command_2->token = TOKEN_LITERAL;
	// next_command_2->next = NULL;
	// command_head_2->next = next_command_2;

	// random_cmd TEST
	command_head = malloc(sizeof(t_command));
	table->simple_command = command_head;
	command_head->content = malloc(sizeof(char) * 4);
	ft_strlcpy(command_head->content, "cd", 4);
	command_head->token = TOKEN_COMMAND;
	command_head->next = NULL;
	
	// next_command = malloc(sizeof(t_command));
	// next_command->content = malloc(sizeof(char) * 20);
	// ft_strlcpy(next_command->content, "", 20);
	// next_command->token = TOKEN_LITERAL;
	// next_command->next = NULL;
	// command_head->next = next_command;

	executor(minishell);
	return (0);
}