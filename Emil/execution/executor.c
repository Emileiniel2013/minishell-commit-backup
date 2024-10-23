/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/23 16:00:06 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	executor(t_minishell *minishell)
{
	char	*content;

	content = minishell->table->simple_command->content;
	if (minishell->table != NULL)
	{
		if (ft_strncmp(content, "echo", ft_strlen(content)) == 0)
			handle_echo(minishell);
		else if (ft_strncmp(content, "pwd", ft_strlen(content)) == 0)
			handle_pwd(minishell);
		else if (ft_strncmp(content, "cd", ft_strlen(content)) == 0)
			handle_cd(minishell);
		else if (ft_strncmp(content, "env", ft_strlen(content)) == 0)
			handle_env(minishell);
		else if (ft_strncmp(content, "export", ft_strlen(content)) == 0)
			handle_export(minishell);
		else if (ft_strncmp(content, "unset", ft_strlen(content)) == 0)
			handle_unset(minishell);
		else if (ft_strncmp(content, "exit", ft_strlen(content)) == 0)
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
			free_minishell(minishell, false);
			if (minishell->success)
				exit(EXIT_SUCCESS);
			else
				exit(minishell->exit_code);
		}
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
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
