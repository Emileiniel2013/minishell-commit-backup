/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:36:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/25 19:32:15 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	replace_env(t_minishell *minishell, char *path)
{
	int		i;
	size_t	size;

	i = 0;
	while (minishell->env[i] != NULL)
	{
		size = ft_strlen(minishell->env[i]);
		if (ft_strnstr(minishell->env[i], "PWD=/", size) != NULL)
			break;
		i++;
	}
	free(minishell->env[i]);
	minishell->env[i] = ft_strjoin("PWD=", path);
}

void	free_arr(char **arr)
{
	int i;

	i = -1;
	if (arr)
	{
		while(arr[++i])
			free(arr[i]);
		free(arr);
	}
	arr = NULL;
}

void	swap_vars(char **newenv)
{
	char	*temp;
	int		i;

	i = 0;
	while (newenv[i] != NULL)
			i++;
	temp = newenv[i - 1];
	newenv[i - 1] = newenv[i - 2];
	newenv[i - 2] = temp;
}

char	**list2array(t_minishell *minishell)
{
	int			i;
	t_command	*cmd;
	char		**arg_arr;

	cmd = minishell->table->simple_command;
	arg_arr = NULL;
	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	arg_arr = malloc(sizeof(char *) * (i + 1));
	arg_arr[i] = NULL;
	cmd = minishell->table->simple_command;
	i = -1;
	while (cmd != NULL)
	{
		arg_arr[++i] = ft_strdup(cmd->content);
		cmd = cmd->next;
	}
	return (arg_arr);
}

char	*ft_getcwd(t_minishell *minishell)
{
	int		i;
	char	*cwd;

	i = -1;
	cwd = NULL;
	while (minishell->env[++i])
	{
		if(ft_strncmp(minishell->env[i], "PWD=", 4) == 0)
		{
			cwd = ft_strdup(minishell->env[i] + 4);
			return (cwd);
		}
	}
	return (NULL);
}

char	**create_arg_lst(t_minishell *minishell)
{
	int			i;
	t_command	*arg_lst;
	char		**arg_arr;

	i = 0;
	arg_arr = NULL;
	arg_lst = minishell->table->simple_command;
	if (arg_lst)
	{
		while(arg_lst)
		{
			arg_lst = arg_lst->next;
			i++;
		}
		arg_arr = malloc (sizeof(char *) * (i + 1));
		arg_arr[i] = NULL;
		i = 0;
		arg_lst = minishell->table->simple_command;
		while(arg_lst)
		{
			arg_arr[i] = ft_strdup(arg_lst->content);
			arg_lst = arg_lst->next;
			i++;
		}
	}
	return (arg_arr);
}

char	*ft_check_var_lst(t_minishell *minishell, char *var)
{
	int		i;
	size_t	len;
	char	*new_var;

	i = -1;
	new_var = NULL;
	len = ft_strlen(var);
	if (!minishell->var_lst)
		return (NULL);
	while(minishell->var_lst[++i])
	{
		if (ft_strncmp(minishell->var_lst[i], var, len) == 0 && minishell->var_lst[i][len] == '=')
		{
			new_var = ft_strdup(minishell->var_lst[i]);
			free(minishell->var_lst[i]);
			while(minishell->var_lst[i + 1])
			{
				minishell->var_lst[i] = minishell->var_lst[i + 1];
				i++;
			}
			minishell->var_lst[i] = NULL;
			if (i == 0)
			{
				free(minishell->var_lst);
				minishell->var_lst = NULL;
			}
			return (new_var);
		}
	}
	return (new_var);
}

void	add_var_to_list(t_minishell *minishell)
{
	int		i;
	char	**var_lst;

	i = 0;
	if (minishell->var_lst)
	{
		while (minishell->var_lst[i])
			i++;
	}
	if (i == 0)
	{
		var_lst = malloc(sizeof(char *) * 2);
		var_lst[0] = ft_strdup(minishell->table->simple_command->content);
		var_lst[1] = NULL;
		minishell->var_lst = var_lst;
	}
	else
	{
		var_lst = malloc(sizeof(char *) * (i + 2));
		var_lst[i + 1] = NULL;
		var_lst[i] = ft_strdup(minishell->table->simple_command->content);
		while (--i >= 0)
			var_lst[i] = ft_strdup(minishell->var_lst[i]);
		free_arr(minishell->var_lst);
		minishell->var_lst = var_lst;
	}
}

int	handle_redirections(t_minishell *minishell)
{
	int	fd;

	if (minishell->in_redir)
	{
		fd = open(minishell->in_redir, O_RDONLY);
		if (fd < 0)
		{
			write(STDERR_FILENO, "Minishell: ", 11);
			write(STDERR_FILENO, minishell->in_redir, ft_strlen(minishell->in_redir));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
			minishell->exit_code = 6;
			minishell->success = false;
			minishell->infd = fd;
			return (-1);
		}
		minishell->infd = fd;
	}
	if (minishell->out_redir)
	{
		if (minishell->append_mode == true)
		{
			fd = open(minishell->out_redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
			minishell->append_mode = false;
		}
		else
			fd = open(minishell->out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			write(STDERR_FILENO, "Minishell: Error opening output file\n", 38);
			minishell->exit_code = 7;
			minishell->success = false;
			minishell->outfd = fd;
			return (-1);
		}
		minishell->outfd = fd;
	}
	return (0);
}

void	restore_redirections(t_minishell *minishell)
{
	if (minishell->in_redir)
	{
		if (minishell->infd > 0)
			close(minishell->infd);
		minishell->infd = STDIN_FILENO;
		free(minishell->in_redir);
		minishell->in_redir = NULL;
	}
	if (minishell->out_redir)
	{
		if (minishell->outfd > 0)
			close(minishell->outfd);
		minishell->outfd = STDOUT_FILENO;
		free(minishell->out_redir);
		minishell->out_redir = NULL;
	}
	if (open(".heredoc_tmp", O_RDONLY, 0644) > 0)
		unlink(".heredoc_tmp");
	if (minishell->success)
		minishell->exit_code = 0;
	else
		minishell->success = true;
}

t_minishell	*init_mini_vars(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	char		**envp_cpy;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	envp_cpy = copy_env(envp);
	minishell->env = envp_cpy;
	minishell->var_lst = NULL;
	minishell->table = NULL;
	minishell->out_redir = NULL;
	minishell->in_redir = NULL;
	minishell->append_mode = false;
	minishell->infd = STDIN_FILENO;
	minishell->outfd = STDOUT_FILENO;
	minishell->exit_code = 0;
	minishell->success = true;
	return (minishell);
}

bool	ft_isnumber(char *content)
{
	while (*content)
	{
		if (*content >= '0' && *content <= '9')
			content++;
		else
			return (false);
	}
	return (true);
}

void	free_minishell(t_minishell *minishell, bool keep_env)
{
	if (minishell->table_head)
		free_table(minishell);
	if (minishell->env && !keep_env)
		free_arr(minishell->env);
	if (minishell->var_lst)
		free_arr(minishell->var_lst);
	if (minishell->in_redir)
	{
		free(minishell->in_redir);
		minishell->in_redir = NULL;
	}
	if (minishell->out_redir)
	{
		free(minishell->out_redir);
		minishell->out_redir = NULL;
	}
	free(minishell);
	minishell = NULL;
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

int	check_existing_var(char *newvar, t_minishell *minishell)
{
	int		i;
	char	*env;
	char	*path;
	char	*target;

	i = 0;
	env = NULL;
	path = NULL;
	target = NULL;
	while(newvar[i] && newvar[i] != '=')
		i++;
	env = ft_strndup(newvar, i);
	path = ft_getenv(minishell, env);
	if (path)
	{
		target = ft_strjoin(env, "=");
		free(env);
		env = ft_strjoin(target, path);
		free(target);
		target = NULL;
		free(path);
		path = NULL;
		i = 0;
		while(minishell->env[i])
		{
			if (ft_strncmp(env, minishell->env[i], ft_strlen(env)) == 0)
			{
				free(minishell->env[i]);
				minishell->env[i] = ft_strdup(newvar);
				free(env);
				env = NULL;
				return (i);
			}
			i++;
		}
	}
	free(env);
	env = NULL;
	return (-1);
}