/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/28 16:44:14 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*check_string(char **content, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*expanded_env;
	char	*temp;
	char	*temp2;

	i = 0;
	j = 0;
	temp = NULL;
	temp2 = NULL;
	expanded_env = NULL;
	while((*content)[i] && (*content)[i] != '$')
		i++;
	if (!(*content)[i])
		return (NULL);
	expanded_env = ft_strndup(*content, i);
	i++;
	if ((*content)[i] == '?')
	{
		temp = ft_itoa(minishell->exit_code);
		i++;
	}
	else
	{
		while ((*content)[i] && (ft_isalnum((*content)[i]) == 1 || (*content)[i] == '_'))
		{
			i++;
			j++;
		}
		temp2 = ft_strndup((*content) + (i - j), j);
		temp = ft_getenv(minishell, temp2);
		free(temp2);
		temp2 = NULL;
	}
	if (temp)
	{
		temp2 = ft_strdup(expanded_env);
		free(expanded_env);
		expanded_env = ft_strjoin(temp2, temp);
		free(temp);
		free(temp2);
		temp2 = NULL;
		temp = NULL;
	}
	if ((*content)[i])
	{
		temp2 = ft_strdup(expanded_env);
		free(expanded_env);
		expanded_env = ft_strjoin(temp2, (*content) + i);
		free(temp);
		free(temp2);
		temp = NULL;
		temp2 = NULL;
	}
	return (expanded_env);
}

char	*ft_getenv(t_minishell *minishell, char	*env)
{
	size_t	i;
	int		len;
	char	*var;

	len = ft_strlen(env);
	i = -1;
	var = NULL;
	while(minishell->env[++i])
	{
		if(ft_strncmp(minishell->env[i], env, len) == 0 && minishell->env[i][len] == '=')
		{
			var = ft_strdup(minishell->env[i] + (len + 1));
			return (var);
		}
	}
	return (var);
}

char	**copy_env(char **envp)
{
	char	**cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	cpy[i] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		{
			cpy[j] = ft_strdup(envp[i]);
			i++;	
			j++;
		}
		else
			i++;
	}
	return (cpy);
}


void	expand_env_vars(char **content, t_minishell *minishell)
{
	char	*expanded_env;

	expanded_env = NULL;
	while (1)
	{
		expanded_env = check_string(content, minishell);
		if (!expanded_env)
			break ;
		else
		{
			free(*content);
			(*content) = ft_strdup(expanded_env);
			free(expanded_env);
			expanded_env = NULL;
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
	if (token_lst->token == TOKEN_STRING || token_lst->token == TOKEN_DOUBLE_QUOTE || token_lst->token == TOKEN_SINGLE_QUOTE)
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
			current_node->cmd_head = current_node->simple_command;
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
		new_node->simple_command = NULL;
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
	free(delimiter);
	delimiter = NULL;
	close(fd); 
	return (0);
}

void	free_table(t_minishell *minishell)
{
	t_command_table *current;
	t_command_table	*next;

	next = NULL;
	current = minishell->table_head;
	while (current)
	{
		next = current->next;
		if (current->cmd_head)
			free_cmd(current->cmd_head);
		free(current);
		current = next;
	}
	minishell->table = NULL;
	minishell->table_head = NULL;
}

void	free_cmd(t_command *cmd)
{
	t_command	*current;
	t_command	*next;

	current = cmd;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
