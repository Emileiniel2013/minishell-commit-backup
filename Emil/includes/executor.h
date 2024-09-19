/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:56:58 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/19 15:38:35 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>

# ifndef STD_OUT
#  define STD_OUT 1
# endif

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_FILENAME,
	TOKEN_ARGUMENT,
	TOKEN_LITERAL,
	TOKEN_OPERATOR,
	TOKEN_SPECIAL,
	TOKEN_UNKNOWN
}		token_type;

typedef struct	t_simple_command
{
	token_type					token;
	char						*content;
	struct	t_simple_command	*next;
}	t_command;

typedef	struct	t_test_struct
{
	bool						leftpipe;
	bool						rightpipe;
	t_command					*simple_command;
	struct t_test_struct		*next;
	char						**envp;
}		command_table;

void	executor(command_table *command);
void	handle_echo(t_command *command);
void	handle_pwd(command_table *table);
void	handle_cd(command_table *table);
char	**copy_env(char **envp);
void	replace_env(command_table *table, char *path);

#endif