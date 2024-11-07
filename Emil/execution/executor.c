/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/07 16:54:26 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	mini_main(t_mini *minish)
{
	int	pipefd[2];
	int	prevpipefd;
	int	pid;

	prevpipefd = -1;
	while (minish->table)
	{
		if (minish->table->rightpipe)
			pipe(pipefd);
		handle_shlvl(minish, '+');
		pid = fork();
		if (pid == 0)
			child_execution(minish, prevpipefd, pipefd);
		parent_execution(minish, pid);
		if (minish->table->leftpipe)
			close(prevpipefd);
		if (minish->table->rightpipe)
			prevpipefd = pipefd[0];
		if (minish->table->leftpipe || minish->table->rightpipe)
			close(pipefd[1]);
		minish->table = minish->table->next;
	}
	if (prevpipefd != -1)
		close(pipefd[0]);
}

void	child_execution(t_mini *minish, int prevpipefd, int *pipefd)
{
	int	status;

	status = 0;
	if (minish->table->leftpipe)
	{
		dup2(prevpipefd, STDIN_FILENO);
		close(prevpipefd);
	}
	else if (!minish->table->leftpipe && minish->in_redir)
		dup2(minish->infd, STDIN_FILENO);
	if (minish->table->rightpipe)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else if (!minish->table->rightpipe && minish->out_redir)
		dup2(minish->outfd, STDOUT_FILENO);
	executor(minish);
	status = minish->exit_code;
	free_minish(minish, false);
	exit(status);
}

void	executor(t_mini *minish)
{
	if (minish->table != NULL)
	{
		if (ft_strcmp(minish->table->command->content, "echo") == 0)
			handle_echo(minish);
		else if (ft_strcmp(minish->table->command->content, "pwd") == 0)
			handle_pwd(minish);
		else if (ft_strcmp(minish->table->command->content, "cd") == 0)
			handle_cd(minish);
		else if (ft_strcmp(minish->table->command->content, "env") == 0)
			handle_env(minish);
		else if (ft_strcmp(minish->table->command->content, "export") == 0)
			handle_export(minish);
		else if (ft_strcmp(minish->table->command->content, "unset") == 0)
			handle_unset(minish);
		else if (ft_strcmp(minish->table->command->content, "exit") == 0)
			handle_exit(minish);
		else if ((ft_strncmp (minish->table->command->content, "./", 2)) == 0)
			execute_file(minish);
		else if (ft_strchr(minish->table->command->content + 1, '=') != NULL)
			add_var_to_list(minish);
		else if (minish->table->command->content[0] == '\0')
			printf("\n");
		else
			check_path(minish);
	}
}

void	parent_execution(t_mini *minish, int pid)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	handle_shlvl(minish, '-');
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
		{
			minish->exit_code = WEXITSTATUS(status);
			minish->success = false;
		}
	}
}

void	execute_file(t_mini *minish)
{
	char	*path;
	char	*filename;

	filename = ft_getcwd(minish);
	path = ft_strjoin(filename, minish->table->command->content + 1);
	ft_free(&filename);
	if (access(path, X_OK) == 0)
		execute_path(minish, path);
	else
	{
		write_err(minish, 22, minish->table->command->content);
		ft_free(&path);
	}
}
