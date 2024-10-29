/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/29 12:35:44 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*check_string(char **content, t_mini *mini)
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
		temp = ft_itoa(mini->exit_code);
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
		temp = ft_getenv(mini, temp2);
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

char	*ft_getenv(t_mini *mini, char	*env)
{
	size_t	i;
	int		len;
	char	*var;

	len = ft_strlen(env);
	i = -1;
	var = NULL;
	while(mini->env[++i])
	{
		if(ft_strncmp(mini->env[i], env, len) == 0 && mini->env[i][len] == '=')
		{
			var = ft_strdup(mini->env[i] + (len + 1));
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


void	expand_env_vars(char **content, t_mini *mini)
{
	char	*expanded_env;

	expanded_env = NULL;
	while (1)
	{
		expanded_env = check_string(content, mini);
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

int	check_valid_redir_input(t_tkn_lst **token_lst, t_mini *mini)
{
	if ((*token_lst)->next == NULL)
	{
		write(STDERR_FILENO, "mini: syntax error near unexpected token `newline'\n", 56);
		mini->exit_code = 8;
		mini->success = false;
		return (-1);
	}
	else if ((*token_lst)->next->token != STRING)
	{
		write(STDERR_FILENO, "mini: syntax error near unexpected token `", 47);
		write(STDERR_FILENO, (*token_lst)->next->content, ft_strlen((*token_lst)->next->content));
		write(STDERR_FILENO, "'\n", 2);
		mini->exit_code = 9;
		mini->success = false;
		return (-1);
	}
	if ((*token_lst)->token == REDIRECT_IN)
	{
		if (mini->in_redir)
			free(mini->in_redir);
		mini->in_redir = ft_strdup((*token_lst)->next->content);
		(*token_lst)->next->token = FILENAME;
	}
	else if ((*token_lst)->token == REDIRECT_OUT || (*token_lst)->token == REDIRECT_OUT_APPEND)
	{
		if (mini->out_redir)
			free(mini->out_redir);
		mini->out_redir = ft_strdup((*token_lst)->next->content);
		(*token_lst)->next->token = FILENAME;
	}
	if ((*token_lst)->token == REDIRECT_OUT_APPEND)
		mini->append_mode = true;
	return (0);
}

int	check_valid_pipe(t_tkn_lst *token_lst, t_table *table, t_mini *mini)
{
	if (token_lst->token == PIPE && (!token_lst->next || token_lst->next->token != STRING))
	{
		write(STDERR_FILENO, "mini: syntax error near unexpected token `newline'\n", 57);
		mini->exit_code = 10;
		mini->success = false;
		return (-1);
	}
	if (token_lst->token == PIPE && !table)
	{
		write(STDERR_FILENO, "mini: syntax error near unexpected token `|'\n", 51);
		mini->exit_code = 11;
		mini->success = false;
		return (-1);
	}
	if (token_lst->token == PIPE && token_lst->next->token != STRING)
	{
		write(STDERR_FILENO, "mini: syntax error near unexpected token `newline'\n",57);
		mini->exit_code = 12;
		mini->success = false;
		return (-1);
	}
	return (0);
}

void	add_token_to_table(t_table **table, t_tkn_lst *token_lst)
{
	t_table *new_node;
	t_table	*current_node;

	new_node = NULL;
	current_node = NULL;
	if (token_lst->token == STRING || token_lst->token == DOUBLE_QUOTE || token_lst->token == SINGLE_QUOTE)
	{
		if (!(*table))
		{
			*table = malloc(sizeof(t_table));
			(*table)->leftpipe = false;
			(*table)->rightpipe = false;
			(*table)->next = NULL;
			(*table)->command = NULL;
		}
		current_node = *table;
		while(current_node->next)
			current_node = current_node->next;
		if (!current_node->command)
		{
			current_node->command = malloc(sizeof(t_cmd));
			current_node->command->content = ft_strdup(token_lst->content);
			current_node->command->next = NULL;
			current_node->cmd_head = current_node->command;
		}
		else
			add_cmd_node(&current_node->command, token_lst->content);
	}
	else if (token_lst->token == PIPE)
	{
		current_node = *table;
		while (current_node->next)
			current_node = current_node->next;
		current_node->rightpipe = true;
		new_node = malloc(sizeof(t_table));
		new_node->leftpipe = true;
		new_node->rightpipe = false;
		new_node->command = NULL;
		new_node->next = NULL;
		current_node->next = new_node;
	}
}

void	add_cmd_node(t_cmd **cmd, char *content)
{
	t_cmd	*new_node;
	t_cmd	*current_node;

	new_node = NULL;
	current_node = NULL;
	new_node = malloc(sizeof(t_cmd)); //ERROR CHECK
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

bool    check_builtin(t_mini *mini)
{
	char	*content;

	content = mini->table->command->content;
	if (mini->table != NULL)
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

int	handle_heredoc(t_tkn_lst **token_lst, t_mini *mini)
{
	char	*delimiter;
	char	*line;
	int		fd;

	line = NULL;
	fd = -1;
	if (!(*token_lst)->next)
	{
		write(STDERR_FILENO, "mini: syntax error near unexpected token 'newline'\n", 57);
		mini->exit_code = 13;
		mini->success = false;
		return (-1);
	}
	if ((*token_lst)->next->token != STRING)
	{
		write(STDERR_FILENO, "mini: syntax error near unexpected token `", 47);
		write(STDERR_FILENO, (*token_lst)->next->content, ft_strlen((*token_lst)->next->content));
		write(STDERR_FILENO, "'\n", 3);
		mini->exit_code = 14;
		mini->success = false;
		return (-1);
	} 
	else
		(*token_lst)->next->token = DELIMITER;
	
	delimiter = ft_strdup((*token_lst)->next->content);
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(STDERR_FILENO, "mini: Failed to create heredoc file\n", 42);
		mini->exit_code = 15;
		mini->success = false;
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
	mini->in_redir = ft_strdup(".heredoc_tmp");
	free(delimiter);
	delimiter = NULL;
	close(fd); 
	return (0);
}

void	free_table(t_mini *mini)
{
	t_table *current;
	t_table	*next;

	next = NULL;
	current = mini->table_head;
	while (current)
	{
		next = current->next;
		if (current->cmd_head)
			free_cmd(current->cmd_head);
		free(current);
		current = next;
	}
	mini->table = NULL;
	mini->table_head = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

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
