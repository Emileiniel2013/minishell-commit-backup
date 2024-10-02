/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/02 14:15:36 by temil-da         ###   ########.fr       */
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

void	mini_main(t_minishell *minishell)
{
	int					pipefd[2];
	int					prevpipefd[2];
	int					pid;

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
				close(prevpipefd[1]);
			}
			if (minishell->table->rightpipe == true)
			{
				dup2(pipefd[1], minishell->std_out_fd);
				close(pipefd[1]);
				close(pipefd[0]);
			}
			executor(minishell);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, NULL, 0);
			if (minishell->table->leftpipe == true)
			{
				close(prevpipefd[0]);
				close(prevpipefd[1]);
			}
			close(pipefd[1]);
			if (minishell->table->rightpipe == true)
			{
				prevpipefd[0] = pipefd[0];
				prevpipefd[1] = pipefd[1];
			}
			else
				close(pipefd[0]);
		}
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
	cpy = malloc(sizeof(char *) * (i + 1));
	cpy[i] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		size = ft_strlen(envp[i]);
		cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (cpy);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_minishell			*minishell;
	command_table		*table;
	// command_table		*table_2;
	// command_table		*table_3;
	t_command			*command_head;
	t_command			*next_command;
	t_command			*current_command;

	char				**envp_cpy;
	int					i;
	(void)argv;
	(void)argc;
	
	
	i = 0;
	minishell = malloc(sizeof(t_minishell));
	table = malloc(sizeof(t_command));
	envp_cpy = copy_env(envp);
	minishell->table = table;
	minishell->env = envp_cpy;
	minishell->std_out_fd = 1;
	minishell->table->leftpipe = false;
	minishell->table->rightpipe = false;
	minishell->table->builtin = true;
	minishell->var_lst = NULL;

	command_head = malloc(sizeof(t_command));
	table->simple_command = command_head;
	command_head->content = malloc(sizeof(char) * 7);
	ft_strlcpy(command_head->content, "export", 7);
	command_head->token = TOKEN_COMMAND;
	
	next_command = malloc(sizeof(t_command));
	next_command->content = malloc(sizeof(char) * 19);
	ft_strlcpy(next_command->content, "VAR1=TestNebun2003", 19);
	next_command->token = TOKEN_LITERAL;
	next_command->next = NULL;
	command_head->next = next_command;

	current_command = next_command;
	next_command = malloc(sizeof(t_command));
	next_command->content = malloc(sizeof(char) * 19);
	ft_strlcpy(next_command->content, "VAR2=TestNebun2009", 19);
	next_command->next = NULL;
	next_command->token = TOKEN_LITERAL;
	current_command->next = next_command;

	execute_file(minishell);
	if (!minishell->table->rightpipe && minishell->table->builtin)
		executor(minishell);
	else
		mini_main(minishell);
	return (0);
}