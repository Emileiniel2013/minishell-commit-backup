/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:36:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/11 20:20:59 by temil-da         ###   ########.fr       */
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

void	free_env(t_minishell *minishell)
{
	int i;

	i = 0;

	while (minishell->env[i] != NULL)
		i++;
	while (i >= 0)
	{
		if (minishell->env[i])
			free(minishell->env[i]);
		i--;
	}
	free(minishell->env);
	if (minishell->var_lst)
	{
		if (!minishell->var_lst[i])
		{
			free(minishell->var_lst);
			minishell->var_lst = NULL;
		}
	}
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
	arg_arr = malloc(sizeof(char *) * i + 1);
	arg_arr[i] = NULL;
	cmd = minishell->table->simple_command;
	i = -1;
	while (cmd != NULL)
	{
		arg_arr[++i] = cmd->content;
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
	arg_lst = minishell->table->simple_command->next;
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
		arg_lst = minishell->table->simple_command->next;
		while(arg_lst)
		{
			arg_arr[i] = ft_strdup(arg_lst->content);
			arg_lst = arg_lst->next;	
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
	len = ft_strlen(var);
	new_var = NULL;
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
	while (minishell->var_lst)
		i++;
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
		while (minishell->var_lst[i])
		{
			free(minishell->var_lst[i]);
			i++;
		}
		free(minishell->var_lst);
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
			printf ("Minishell: %s: No such file or directory\n", minishell->in_redir);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		minishell->infd = fd;
	}
	if (minishell->out_redir)
	{
		if (minishell->append_mode == TRUE)
			fd = open(minishell->out_redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(minishell->out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			printf("Minishell: Error opening output file\n");
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
		dup2(minishell->infd, STDIN_FILENO);
		close(minishell->infd);
		minishell->infd = STDIN_FILENO;
	}
	if (minishell->out_redir)
	{
		dup2(minishell->outfd, STDOUT_FILENO);
		close(minishell->outfd);
		minishell->outfd = STDOUT_FILENO;
	}
}

