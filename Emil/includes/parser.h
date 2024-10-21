/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:32:53 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/19 19:02:39 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "lexer.h"
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	t_simple_command
{
	char						*content;
	struct	t_simple_command	*next;
}	t_command;

typedef	struct	t_test_struct
{
	bool						leftpipe;
	bool						rightpipe;
	t_command					*simple_command;
	struct t_test_struct		*next;
}		t_command_table;

typedef struct t_minishell
{
	t_command_table	*table;
	char			**env;
	char			**var_lst;
	char			*out_redir;
	int				outfd;
	char			*in_redir;
	int				infd;
	bool			append_mode;
}		t_minishell;

char	**copy_env(char **envp);
void	parse_input(char *line, t_minishell *minishell);
void	expand_env_vars(char **content, t_minishell *minishell, token_type token);
char	*ft_getenv(t_minishell *minishell, char	*env);
char	*check_quoted_string(char **content, t_minishell *minishell);
int		check_valid_redir_input(t_tokens **token_lst, t_minishell *minishell);
int		check_valid_pipe(t_tokens *token_lst, t_command_table *table);
void	add_token_to_table(t_command_table **table, t_tokens *token_lst);
void	add_cmd_node(t_command **cmd, char *content);
bool    check_builtin(t_minishell *minishell);
int		handle_heredoc(t_tokens **token_lst, t_minishell *minishell);

#endif