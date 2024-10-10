/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/08 13:02:05 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

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
		else if ((ft_strncmp (minishell->table->simple_command->content, "./", 2)) == 0)
			execute_file(minishell);
		else if (ft_strchr(minishell->table->simple_command->content + 1, "=") != NULL)
			add_var_to_list(minishell);
		else if (minishell->table->simple_command->content[0] == '\0')
			printf("\n");
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
				dup2(pipefd[1], STDOUT_FILENO);
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
