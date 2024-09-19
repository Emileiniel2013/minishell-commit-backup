/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:24:36 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/19 15:47:11 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/executor.h"

void	handle_echo(t_command *command)
{
	t_command	*command_cpy;
	bool		nl;

	nl = true;
	command_cpy = command;
	if (command_cpy->token == TOKEN_ARGUMENT)
	{
		nl = false;
		command_cpy = command_cpy->next;
	}
	while (command_cpy != NULL)
	{
		printf("%s", command_cpy->content);
		command_cpy = command_cpy->next;
		if (command_cpy != NULL)
			printf(" ");
	}
	if (nl == true)
		printf("\n");
}

void	handle_pwd(command_table *table)
{
	char	*line;
	int		i;
	size_t	size;

	line = NULL;
	size = 0;
	i = 0;
	while (table->envp[i] != NULL)
	{
		size = ft_strlen(table->envp[i]);
		if (ft_strnstr(table->envp[i], "PWD=/", size) != NULL)
		{
			line = malloc(sizeof(char) * size + 1);
			ft_strlcpy(line, table->envp[i], size + 1);
			break;
		}
		i++;
	}
	i = 4;
	while (line[i])
	{
		write(1, &line[i], 1);
		i++;
	}
	write (1, "\n", 1);
}

void	handle_cd(command_table *table)
{
	char	*path;
	char	cwd[1024];

	path = table->simple_command->next->content;
	if (chdir(path) != 0)
	{
		printf("Minishell: cd: %s: No such file or directory\n", path);
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	replace_env(table, cwd);
}