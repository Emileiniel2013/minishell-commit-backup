/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:36:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/30 17:19:26 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	replace_env(t_mini *mini, char *path, char *env)
{
	int		i;
	size_t	size;
	bool	found_env;
	char	**newenv;

	i = 0;
	found_env = false;
	newenv = NULL;
	while (mini->env[i])
	{
		size = ft_strlen(mini->env[i]);
		if (ft_strnstr(mini->env[i], env, size) != NULL)
		{
			found_env = true;
			break;
		}
		i++;
	}
	if (found_env)
	{
		free(mini->env[i]);
		mini->env[i] = ft_strjoin(env, path);
	}
	else
	{
		newenv = malloc(sizeof(char *) * (i + 2));
		newenv[i + 1] = NULL;
		newenv[i] = ft_strjoin(env, path);
		while (--i >= 0)
			newenv[i] = ft_strdup(mini->env[i]);
		swap_vars(newenv);
		free_arr(mini->env);
		mini->env = newenv;
	}
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

char	**list2array(t_mini *mini)
{
	int		i;
	t_cmd	*cmd;
	char	**arg_arr;

	cmd = mini->table->command;
	arg_arr = NULL;
	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	arg_arr = malloc(sizeof(char *) * (i + 1));
	arg_arr[i] = NULL;
	cmd = mini->table->command;
	i = -1;
	while (cmd != NULL)
	{
		arg_arr[++i] = ft_strdup(cmd->content);
		cmd = cmd->next;
	}
	return (arg_arr);
}

char	*ft_getcwd(t_mini *mini)
{
	int		i;
	char	*cwd;

	i = -1;
	cwd = NULL;
	while (mini->env[++i])
	{
		if(ft_strncmp(mini->env[i], "PWD=", 4) == 0)
		{
			cwd = ft_strdup(mini->env[i] + 4);
			return (cwd);
		}
	}
	return (NULL);
}

char	**create_arg_lst(t_mini *mini)
{
	int			i;
	t_cmd	*arg_lst;
	char		**arg_arr;

	i = 0;
	arg_arr = NULL;
	arg_lst = mini->table->command;
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
		arg_lst = mini->table->command;
		while(arg_lst)
		{
			arg_arr[i] = ft_strdup(arg_lst->content);
			arg_lst = arg_lst->next;
			i++;
		}
	}
	return (arg_arr);
}

char	*ft_check_var_lst(t_mini *mini, char *var)
{
	int		i;
	size_t	len;
	char	*new_var;

	i = -1;
	new_var = NULL;
	len = ft_strlen(var);
	if (!mini->var_lst)
		return (NULL);
	while(mini->var_lst[++i])
	{
		if (ft_strncmp(mini->var_lst[i], var, len) == 0 && mini->var_lst[i][len] == '=')
		{
			new_var = ft_strdup(mini->var_lst[i]);
			free(mini->var_lst[i]);
			while(mini->var_lst[i + 1])
			{
				mini->var_lst[i] = mini->var_lst[i + 1];
				i++;
			}
			mini->var_lst[i] = NULL;
			if (i == 0)
			{
				free(mini->var_lst);
				mini->var_lst = NULL;
			}
			return (new_var);
		}
	}
	return (new_var);
}

void	add_var_to_list(t_mini *mini)
{
	int		i;
	char	**var_lst;

	i = 0;
	if (mini->var_lst)
	{
		while (mini->var_lst[i])
			i++;
	}
	if (i == 0)
	{
		var_lst = malloc(sizeof(char *) * 2);
		var_lst[0] = ft_strdup(mini->table->command->content);
		var_lst[1] = NULL;
		mini->var_lst = var_lst;
	}
	else
	{
		var_lst = malloc(sizeof(char *) * (i + 2));
		var_lst[i + 1] = NULL;
		var_lst[i] = ft_strdup(mini->table->command->content);
		while (--i >= 0)
			var_lst[i] = ft_strdup(mini->var_lst[i]);
		free_arr(mini->var_lst);
		mini->var_lst = var_lst;
	}
}

int	handle_redirections(t_mini *mini)
{
	int	fd;

	if (mini->in_redir)
	{
		fd = open(mini->in_redir, O_RDONLY);
		if (fd < 0)
		{
			write(STDERR_FILENO, "mini: ", 11);
			write(STDERR_FILENO, mini->in_redir, ft_strlen(mini->in_redir));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
			mini->exit_code = 6;
			mini->success = false;
			mini->infd = fd;
			return (-1);
		}
		mini->infd = fd;
	}
	if (mini->out_redir)
	{
		if (mini->append_mode == true)
		{
			fd = open(mini->out_redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
			mini->append_mode = false;
		}
		else
			fd = open(mini->out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			write(STDERR_FILENO, "mini: Error opening output file\n", 38);
			mini->exit_code = 7;
			mini->success = false;
			mini->outfd = fd;
			return (-1);
		}
		mini->outfd = fd;
	}
	return (0);
}

void	restore_redirections(t_mini *mini)
{
	if (mini->in_redir)
	{
		if (mini->infd > 0)
			close(mini->infd);
		mini->infd = STDIN_FILENO;
		free(mini->in_redir);
		mini->in_redir = NULL;
	}
	if (mini->out_redir)
	{
		if (mini->outfd > 0)
			close(mini->outfd);
		mini->outfd = STDOUT_FILENO;
		free(mini->out_redir);
		mini->out_redir = NULL;
	}
	if (open(".heredoc_tmp", O_RDONLY, 0644) > 0)
		unlink(".heredoc_tmp");
	if (mini->success)
		mini->exit_code = 0;
	else
		mini->success = true;
}

t_mini	*init_mini_vars(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char		**envp_cpy;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_mini));
	envp_cpy = copy_env(envp);
	mini->env = envp_cpy;
	mini->var_lst = NULL;
	mini->table = NULL;
	mini->table_head = NULL;
	mini->out_redir = NULL;
	mini->in_redir = NULL;
	mini->append_mode = false;
	mini->infd = STDIN_FILENO;
	mini->outfd = STDOUT_FILENO;
	mini->exit_code = 0;
	mini->success = true;
	return (mini);
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

void	free_mini(t_mini *mini, bool keep_env)
{
	if (mini->table_head)
		free_table(mini);
	if (mini->env && !keep_env)
		free_arr(mini->env);
	if (mini->var_lst)
		free_arr(mini->var_lst);
	if (mini->in_redir)
	{
		free(mini->in_redir);
		mini->in_redir = NULL;
	}
	if (mini->out_redir)
	{
		free(mini->out_redir);
		mini->out_redir = NULL;
	}
	free(mini);
	mini = NULL;
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

int	check_existing_var(char *newvar, t_mini *mini)
{
	int		i;
	int		j;
	char	*env;
	char	*path;
	char	*target;
	bool	join;

	i = 0;
	j = 0;
	env = NULL;
	path = NULL;
	target = NULL;
	join = false;
	while(newvar[i] && newvar[i] != '=')
		i++;
	if (newvar[i - 1] == '+')
	{
		join = true;
		env = ft_strndup(newvar, i - 1);
	}
	else
		env = ft_strndup(newvar, i);
	path = ft_getenv(mini, env);
	if (path)
	{
		target = ft_strjoin(env, "=");
		free(env);
		env = ft_strjoin(target, path); //perfect so far
		free(target);
		target = NULL;
		free(path);
		path = NULL;
		i = 0;
		while(mini->env[i])
		{
			if (ft_strncmp(env, mini->env[i], ft_strlen(env)) == 0)
			{
				free(mini->env[i]);
				if (join)
				{
					while(newvar[j] != '=')
						j++;
					path = ft_strjoin(env, newvar + j + 1);
					mini->env[i] = ft_strdup(path);
					free(path);
					path = NULL;
				}
				else
					mini->env[i] = ft_strdup(newvar);
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

void	handle_shlvl(t_mini *mini, char sign)
{
	char	*num;
	char	**newenv;
	int		i;

	num = NULL;
	num = ft_getenv(mini, "SHLVL");
	i = -1;
	newenv = NULL;
	if (!num || !ft_isnumber(num))
	{
		while (mini->env[++i] != NULL)
			;
		newenv = malloc(sizeof(char *) * (i + 2));
		newenv[i + 1] = NULL;
		newenv[i] = ft_strdup("SHLVL=1");
		while (--i >= 0)
			newenv[i] = ft_strdup(mini->env[i]);
		swap_vars(newenv);
		free_arr(mini->env);
		mini->env = newenv;
		if (num)
		{
			free(num);
			num = NULL;
		}
		return ;
	}
	i = ft_atoi(num);
	if (sign == '+')
		i++;
	else
		i--;
	free(num);
	num = ft_itoa(i);
	replace_env(mini, num, "SHLVL=");
	free(num);
	num = NULL;
}

bool	check_nl(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '\0')
		return (false);
	while (content[i])
	{
		if (i == 0 && content[i] == '-')
			i++;
		else if (content[i] == 'n')
			i++;
		else
			return (false);
	}
	return (true);
}

bool    check_builtin(t_mini *minish)
{
	char	*content;

	content = minish->table->command->content;
	if (minish->table != NULL)
	{
		if (ft_strcmp(content, "echo") == 0)
			return (true);
		else if (ft_strcmp(content, "pwd") == 0)
			return (true);
		else if (ft_strcmp(content, "cd") == 0)
			return (true);
		else if (ft_strcmp(content, "env") == 0)
			return (true);
		else if (ft_strcmp(content, "export") == 0)
			return (true);
		else if (ft_strcmp(content, "unset") == 0)
			return (true);
		else if (ft_strcmp(content, "exit") == 0)
			return (true);
		else if (ft_strchr(content + 1, '=') != NULL)
			return (true);
		else
			return (false);
		}
	return (false);
}