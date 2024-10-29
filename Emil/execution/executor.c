/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:41:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/28 20:23:33 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	executor(t_mini *mini)
{
	char	*content;

	content = mini->table->command->content;
	if (mini->table != NULL)
	{
		if (ft_strcmp(content, "echo") == 0)
			handle_echo(mini);
		else if (ft_strcmp(content, "pwd") == 0)
			handle_pwd(mini);
		else if (ft_strcmp(content, "cd") == 0)
			handle_cd(mini);
		else if (ft_strcmp(content, "env") == 0)
			handle_env(mini);
		else if (ft_strcmp(content, "export") == 0)
			handle_export(mini);
		else if (ft_strcmp(content, "unset") == 0)
			handle_unset(mini);
		else if (ft_strcmp(content, "exit") == 0)
			handle_exit(mini);
		else if ((ft_strncmp (content, "./", 2)) == 0)
			execute_file(mini);
		else if (ft_strchr(content + 1, '=') != NULL)
			add_var_to_list(mini);
		else if (content[0] == '\0')
			printf("\n");
		else
			check_path(mini);
	}
}

void	mini_main(t_mini *mini)
{
	int	pipefd[2];
	int	prevpipefd;
	int	pid;
	int	status;

	status = 0;
	prevpipefd = -1;
	while(mini->table)
	{
		if (mini->table->rightpipe)
			pipe(pipefd);
		handle_shlvl(mini, '+');
		pid = fork();
		if (pid == 0)
		{
			if (mini->table->leftpipe)
			{
				dup2(prevpipefd, STDIN_FILENO);
				close(prevpipefd);
			}
			else if (!mini->table->leftpipe && mini->in_redir)
				dup2(mini->infd, STDIN_FILENO);
			if (mini->table->rightpipe)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			else if (!mini->table->rightpipe && mini->out_redir)
				dup2(mini->outfd, STDOUT_FILENO);
			executor(mini);
			if (mini->success)
			{
				free_mini(mini, false);
				exit(EXIT_SUCCESS);
			}
			else
			{
				status = mini->exit_code;
				free_mini(mini, false);
				exit(status);
			}
		}
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		handle_shlvl(mini, '-');
		signal(SIGINT, sigint_handler);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
			{
				mini->exit_code = WEXITSTATUS(status);
				mini->success = false;
			}
		}
		if (mini->table->leftpipe)
			close(prevpipefd);
		if (mini->table->rightpipe)
			prevpipefd = pipefd[0];
		if (mini->table->leftpipe || mini->table->rightpipe)
			close(pipefd[1]);
		mini->table = mini->table->next;
	}
	if (prevpipefd != -1)
		close(pipefd[0]);
}
