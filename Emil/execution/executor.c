/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/29 13:17:08 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	executor(t_mini *minish)
{
	char	*content;

	content = minish->table->command->content;
	if (minish->table != NULL)
	{
		if (ft_strcmp(content, "echo") == 0)
			handle_echo(minish);
		else if (ft_strcmp(content, "pwd") == 0)
			handle_pwd(minish);
		else if (ft_strcmp(content, "cd") == 0)
			handle_cd(minish);
		else if (ft_strcmp(content, "env") == 0)
			handle_env(minish);
		else if (ft_strcmp(content, "export") == 0)
			handle_export(minish);
		else if (ft_strcmp(content, "unset") == 0)
			handle_unset(minish);
		else if (ft_strcmp(content, "exit") == 0)
			handle_exit(minish);
		else if ((ft_strncmp (content, "./", 2)) == 0)
			execute_file(minish);
		else if (ft_strchr(content + 1, '=') != NULL)
			add_var_to_list(minish);
		else if (content[0] == '\0')
			printf("\n");
		else
			check_path(minish);
	}
}

void	mini_main(t_mini *minish)
{
	int	pipefd[2];
	int	prevpipefd;
	int	pid;
	int	status;

	status = 0;
	prevpipefd = -1;
	while(minish->table)
	{
		if (minish->table->rightpipe)
			pipe(pipefd);
		handle_shlvl(minish, '+');
		pid = fork();
		if (pid == 0)
		{
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
			if (minish->success)
			{
				free_mini(minish, false);
				exit(EXIT_SUCCESS);
			}
			else
			{
				status = minish->exit_code;
				free_mini(minish, false);
				exit(status);
			}
		}
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		handle_shlvl(minish, '-');
		signal(SIGINT, sigint_handler);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
			{
				minish->exit_code = WEXITSTATUS(status);
				minish->success = false;
			}
		}
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
