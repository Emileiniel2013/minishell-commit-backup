/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/21 17:18:35 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*check_quoted_string(char **content, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*expanded_env;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	expanded_env = NULL;
	while((*content)[i] && (*content)[i] != '$')
		i++;
	if (!(*content)[i])
		return (NULL);
	expanded_env = ft_strndup(*content, i);
	i++;
	while ((*content)[i] && (ft_isalnum((*content)[i]) == 1 || (*content)[i] == '_'))
	{
		i++;
		j++;
	}
	temp = ft_strndup((*content) + (i - j), j);
	temp = ft_getenv(minishell, temp);
	if (temp)
		expanded_env = ft_strjoin(expanded_env, temp);
	if ((*content)[i])
		expanded_env = ft_strjoin(expanded_env, (*content) + i);
	return (expanded_env);
}

char	*ft_getenv(t_minishell *minishell, char	*env)
{
	size_t	i;
	int		len;
	char	*var;

	len = ft_strlen(env);
	i = -1;
	while(minishell->env[++i])
	{
		if(ft_strncmp(minishell->env[i], env, len) == 0 && minishell->env[i][len] == '=')
		{
			var = ft_strdup(minishell->env[i] + len + 1);
			return (var);
		}
	}
	return (NULL);
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


void	expand_env_vars(char **content, t_minishell *minishell, token_type token)
{
	char	*expanded_env;

	expanded_env = NULL;
	if (token == TOKEN_STRING)
	{
		if ((*content)[0] == '$')
		{
			if (ft_strncmp(*content, "$?", ft_strlen(*content)) == 0)
			{
				free(*content);
				*content = ft_itoa(minishell->exit_code);
				return ;
			}
			expanded_env = ft_getenv(minishell, *content + 1);
			if (expanded_env == NULL)
			{
				free(*content);
				*content = ft_strdup("");
			}
			else
			{
				free(*content);
				*content = ft_strdup(expanded_env);
				free(expanded_env);
			}
		}
	}
	else
	{
		while (1)
		{
			expanded_env = check_quoted_string(content, minishell);
			if (!expanded_env)
				break ;
			else
			{
				free(*content);
				(*content) = expanded_env;
			}
		}
	}
}

int	check_valid_redir_input(t_tokens **token_lst, t_minishell *minishell)
{
	if ((*token_lst)->next == NULL)
	{
		write(STDERR_FILENO, "Minishell: syntax error near unexpected token `newline'\n", 56);
		minishell->exit_code = 8;
		minishell->success = false;
		return (-1);
	}
	else if ((*token_lst)->next->token != TOKEN_STRING)
	{
		write(STDERR_FILENO, "Minishell: syntax error near unexpected token `", 47);
		write(STDERR_FILENO, (*token_lst)->next->content, ft_strlen((*token_lst)->next->content));
		write(STDERR_FILENO, "'\n", 2);
		minishell->exit_code = 9;
		minishell->success = false;
		return (-1);
	}
	if ((*token_lst)->token == TOKEN_REDIRECT_IN)
	{
		if (minishell->in_redir)
			free(minishell->in_redir);
		minishell->in_redir = ft_strdup((*token_lst)->next->content);
		(*token_lst)->next->token = TOKEN_FILENAME;
	}
	else if ((*token_lst)->token == TOKEN_REDIRECT_OUT || (*token_lst)->token == TOKEN_REDIRECT_OUT_APPEND)
	{
		if (minishell->out_redir)
			free(minishell->out_redir);
		minishell->out_redir = ft_strdup((*token_lst)->next->content);
		(*token_lst)->next->token = TOKEN_FILENAME;
	}
	if ((*token_lst)->token == TOKEN_REDIRECT_OUT_APPEND)
		minishell->append_mode = true;
	return (0);
}

int	check_valid_pipe(t_tokens *token_lst, t_command_table *table, t_minishell *minishell)
{
	if (token_lst->token == TOKEN_PIPE && (!token_lst->next || token_lst->next->token != TOKEN_STRING))
	{
		write(STDERR_FILENO, "Minishell: syntax error near unexpected token `newline'\n", 57);
		minishell->exit_code = 10;
		minishell->success = false;
		return (-1);
	}
	if (token_lst->token == TOKEN_PIPE && !table)
	{
		write(STDERR_FILENO, "Minishell: syntax error near unexpected token `|'\n", 51);
		minishell->exit_code = 11;
		minishell->success = false;
		return (-1);
	}
	if (token_lst->token == TOKEN_PIPE && token_lst->next->token != TOKEN_STRING)
	{
		write(STDERR_FILENO, "Minishell: syntax error near unexpected token `newline'\n",57);
		minishell->exit_code = 12;
		minishell->success = false;
		return (-1);
	}
	return (0);
}

void	add_token_to_table(t_command_table **table, t_tokens *token_lst)
{
	t_command_table *new_node;
	t_command_table	*current_node;

	new_node = NULL;
	current_node = NULL;
	if (token_lst->token == TOKEN_STRING || token_lst->token == TOKEN_DOUBLE_QUOTE)
	{
		if (!(*table))
		{
			*table = malloc(sizeof(t_command_table));
			(*table)->leftpipe = false;
			(*table)->rightpipe = false;
			(*table)->next = NULL;
			(*table)->simple_command = NULL;
		}
		current_node = *table;
		while(current_node->next)
			current_node = current_node->next;
		if (!current_node->simple_command)
		{
			current_node->simple_command = malloc(sizeof(t_command));
			current_node->simple_command->content = ft_strdup(token_lst->content);
			current_node->simple_command->next = NULL;
		}
		else
			add_cmd_node(&current_node->simple_command, token_lst->content);
	}
	else if (token_lst->token == TOKEN_PIPE)
	{
		current_node = *table;
		while (current_node->next)
			current_node = current_node->next;
		current_node->rightpipe = true;
		new_node = malloc(sizeof(t_command_table));
		new_node->leftpipe = true;
		new_node->rightpipe = false;
		new_node->next = NULL;
		current_node->next = new_node;
	}
}

void	add_cmd_node(t_command **cmd, char *content)
{
	t_command	*new_node;
	t_command	*current_node;

	new_node = NULL;
	current_node = NULL;
	new_node = malloc(sizeof(t_command)); //ERROR CHECK
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	if (!(*cmd))
		*cmd = new_node;
	else
	{
		current_node = (*cmd);
		while(current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
}

bool    check_builtin(t_minishell *minishell)
{
	char	*content;

	content = minishell->table->simple_command->content;
	if (minishell->table != NULL)
	{
		if (ft_strncmp(content, "echo", ft_strlen(content)) == 0)
			return (true);
		else if (ft_strncmp(content, "pwd", ft_strlen(content)) == 0)
			return (true);
		else if (ft_strncmp(content, "cd", ft_strlen(content)) == 0)
			return (true);
		else if (ft_strncmp(content, "env", ft_strlen(content)) == 0)
			return (true);
		else if (ft_strncmp(content, "export", ft_strlen(content)) == 0)
			return (true);
		else if (ft_strncmp(content, "unset", ft_strlen(content)) == 0)
			return (true);
		else if (ft_strchr(content + 1, '=') != NULL)
			return (true);
		else
			return (false);
		}
	return (false);
}

int	handle_heredoc(t_tokens **token_lst, t_minishell *minishell)
{
	char	*delimiter;
	char	*line;
	int		fd;

	line = NULL;
	fd = -1;
	if (!(*token_lst)->next)
	{
		write(STDERR_FILENO, "Minishell: syntax error near unexpected token 'newline'\n", 57);
		minishell->exit_code = 13;
		minishell->success = false;
		return (-1);
	}
	if ((*token_lst)->next->token != TOKEN_STRING)
	{
		write(STDERR_FILENO, "Minishell: syntax error near unexpected token `", 47);
		write(STDERR_FILENO, (*token_lst)->next->content, ft_strlen((*token_lst)->next->content));
		write(STDERR_FILENO, "'\n", 3);
		minishell->exit_code = 14;
		minishell->success = false;
		return (-1);
	} 
	else
		(*token_lst)->next->token = TOKEN_DELIMITER;
	
	delimiter = ft_strdup((*token_lst)->next->content);
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(STDERR_FILENO, "Minishell: Failed to create heredoc file\n", 42);
		minishell->exit_code = 15;
		minishell->success = false;
		return (-1);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
	}
	minishell->in_redir = ft_strdup(".heredoc_tmp");
	close(fd); 
	return (0);
}