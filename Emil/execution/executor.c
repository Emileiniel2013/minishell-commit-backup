/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/28 17:23:37 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	executor(t_minishell *minishell)
{
	char	*content;

	content = minishell->table->simple_command->content;
	if (minishell->table != NULL)
	{
		if (ft_strcmp(content, "echo") == 0)
			handle_echo(minishell);
		else if (ft_strcmp(content, "pwd") == 0)
			handle_pwd(minishell);
		else if (ft_strcmp(content, "cd") == 0)
			handle_cd(minishell);
		else if (ft_strcmp(content, "env") == 0)
			handle_env(minishell);
		else if (ft_strcmp(content, "export") == 0)
			handle_export(minishell);
		else if (ft_strcmp(content, "unset") == 0)
			handle_unset(minishell);
		else if (ft_strcmp(content, "exit") == 0)
			handle_exit(minishell);
		else if ((ft_strncmp (content, "./", 2)) == 0)
			execute_file(minishell);
		else if (ft_strchr(content + 1, '=') != NULL)
			add_var_to_list(minishell);
		else if (content[0] == '\0')
			printf("\n");
		else
			check_path(minishell);
	}
}

void	mini_main(t_minishell *minishell)
{
	int	pipefd[2];
	int	prevpipefd;
	int	pid;
	int	status;

	status = 0;
	prevpipefd = -1;
	while(minishell->table)
	{
		if (minishell->table->rightpipe)
			pipe(pipefd);
		handle_shlvl(minishell, '+');
		pid = fork();
		if (pid == 0)
		{
			if (minishell->table->leftpipe)
			{
				dup2(prevpipefd, STDIN_FILENO);
				close(prevpipefd);
			}
			else if (!minishell->table->leftpipe && minishell->in_redir)
				dup2(minishell->infd, STDIN_FILENO);
			if (minishell->table->rightpipe)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			else if (!minishell->table->rightpipe && minishell->out_redir)
				dup2(minishell->outfd, STDOUT_FILENO);
			executor(minishell);
			if (minishell->success)
			{
				free_minishell(minishell, false);
				exit(EXIT_SUCCESS);
			}
			else
			{
				status = minishell->exit_code;
				free_minishell(minishell, false);
				exit(status);
			}
		}
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		handle_shlvl(minishell, '-');
		signal(SIGINT, sigint_handler);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
			{
				minishell->exit_code = WEXITSTATUS(status);
				minishell->success = false;
			}
		}
		if (minishell->table->leftpipe)
			close(prevpipefd);
		if (minishell->table->rightpipe)
			prevpipefd = pipefd[0];
		if (minishell->table->leftpipe || minishell->table->rightpipe)
			close(pipefd[1]);
		minishell->table = minishell->table->next;
	}
	if (prevpipefd != -1)
		close(pipefd[0]);
}
