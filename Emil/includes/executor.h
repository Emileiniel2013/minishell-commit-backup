/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:56:58 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/02 17:03:12 by tndreka          ###   ########.fr       */
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

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_FILENAME,
	TOKEN_ARGUMENT,
	TOKEN_LITERAL,
	TOKEN_OPERATOR,
	TOKEN_SPECIAL,
	TOKEN_INVALID_ARG,
	TOKEN_EXECUTABLE,
	TOKEN_UNKNOWN
}token_type;

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
	bool						builtin;
	t_command					*simple_command;
	struct t_test_struct		*next;
}		command_table;

typedef struct t_minishell
{
	command_table	*table;
	char			**env;
	int				std_out_fd;
	char			**var_lst;
}		t_minishell;

void	executor(t_minishell *minishell);
void	handle_echo(t_minishell *minishell);
void	handle_pwd(t_minishell *minishell);
void	handle_cd(t_minishell *minishell);
void	handle_env(t_minishell *minishell);
void	handle_export(t_minishell *minishell);
void	handle_unset(t_minishell *minishell);
void	execute_file(t_minishell *minishell);
void	check_path(t_minishell *minishell);
char	**list2array(t_minishell *minishell);
char	**copy_env(char **envp);
void	free_env(t_minishell *minishell);
void	swap_vars(char **newenv);
void	replace_env(t_minishell *minishell, char *path);
char	*ft_getcwd(t_minishell *minishell);
char	*ft_getenv(t_minishell *minishell, char	*env);
char	**create_arg_lst(t_minishell *minishell);

#endif