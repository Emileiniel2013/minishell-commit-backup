/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/25 17:21:54 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/executor.h"

void	executor(t_minishell *minishell)
{
	if (minishell->table != NULL)
	{
		if (ft_strncmp(minishell->table->simple_command->content, "echo", 4) == 0)
			handle_echo(minishell);
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
		else if (minishell->table->simple_command->token == TOKEN_EXECUTABLE)
			execute_file(minishell);
		else
			check_path(minishell);
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
	command_table		*table_2;
	command_table		*table_3;
	t_command			*command_head;
	t_command			*next_command;
	// t_command			*current_command;

	char				**envp_cpy;
	int					i;
	int					pid;
	int					pipefd[2];
	int					prevpipefd[2];
	(void)argv;
	(void)argc;
	
	i = 0;
	minishell = malloc(sizeof(t_minishell));
	envp_cpy = copy_env(envp);
	minishell->env = envp_cpy;
	minishell->std_out_fd = 1;

	// first cmd in pipeline ---  ls -l
	table = malloc(sizeof(command_table));
	minishell->table = table;
	table->leftpipe = false;
	table->rightpipe = true;
	command_head = malloc(sizeof(t_command));
	table->simple_command = command_head;
	command_head->content = malloc(sizeof(char) * 4);
	ft_strlcpy(command_head->content, "/ls", 4);
	command_head->token = TOKEN_COMMAND;
	next_command = malloc(sizeof(t_command));
	command_head->next = next_command;
	next_command->token = TOKEN_ARGUMENT;
	next_command->content = malloc(sizeof(char) * 3);
	ft_strlcpy(next_command->content, "-l", 3);
	next_command->next = NULL;

	// second cmd in pipeline --- grep helper  // should take the output of ls -l and output the line containing "helper"
	table_2 = malloc(sizeof(t_minishell));
	table->next = table_2;
	table_2->leftpipe = true;
	table_2->rightpipe = true;
	command_head = malloc(sizeof(t_command));
	table_2->simple_command = command_head;
	command_head->content = malloc(sizeof(char) * 6);
	ft_strlcpy(command_head->content, "/grep", 6);
	command_head->token = TOKEN_COMMAND;
	next_command = malloc(sizeof(t_command));
	command_head->next = next_command;
	next_command->token = TOKEN_ARGUMENT;
	next_command->content = malloc(sizeof(char) * 7);
	ft_strlcpy(next_command->content, "helper", 7);
	next_command->next = NULL;

	// third cmd in pipeline --- echo Hello :) ---- This one should ignore the pipe output redir and do it's own thing so maybe not best decision atm but still we try it like this first
	table_3 = malloc(sizeof(command_table));
	table_2->next = table_3;
	table_3->leftpipe = true;
	table_3->rightpipe = false;
	command_head = malloc(sizeof(t_command));
	table_3->simple_command = command_head;
	command_head->content = malloc(sizeof(char) * 6);
	ft_strlcpy(command_head->content, "echo", 6);
	command_head->token = TOKEN_COMMAND;
	next_command = malloc(sizeof(t_command));
	command_head->next = next_command;
	next_command->token = TOKEN_ARGUMENT;
	next_command->content = malloc(sizeof(char) * 7);
	ft_strlcpy(next_command->content, "Hello", 7);
	next_command->next = NULL;
	table_3->next = NULL;


	while(minishell->table != NULL)
	{
		if (minishell->table->rightpipe == true)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			if (minishell->table->leftpipe == true)
			{
				dup2(prevpipefd[0], STDIN_FILENO);
				close(prevpipefd[0]);
			}
			if (minishell->table->rightpipe == true)
			{
				dup2(pipefd[1], minishell->std_out_fd);
				close(pipefd[1]);
			}
			executor(minishell);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(pipefd[1]);
			if (minishell->table->leftpipe == true)
				close(prevpipefd[0]);
			prevpipefd[0] = pipefd[0];
			prevpipefd[1] = pipefd[1];
		}
		minishell->table = minishell->table->next;
	}
	return (0);
}