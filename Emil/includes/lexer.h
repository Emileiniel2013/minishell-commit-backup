/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:27:42 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/30 13:25:13 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum token_type
{
	COMMAND,
	FILENAME,
	ARGUMENT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	REDIRIN,
	REDIROUT,
	REDIROUTAPP,
	HEREDOC,
	DELIMITER,
	STRING,
	UNKNOWN
}	t_tkn;

typedef struct t_tokenizer
{
	char				*content;
	t_tkn				tkn;
	struct t_tokenizer	*next;
}		t_tkn_lst;

typedef struct t_simple_command
{
	char						*content;
	struct t_simple_command		*next;
}	t_cmd;

typedef struct t_command_table
{
	bool						leftpipe;
	bool						rightpipe;
	t_cmd						*command;
	t_cmd						*cmd_head;
	struct t_command_table		*next;
}		t_table;

typedef struct t_minishell
{
	t_table	*table;
	t_table	*table_head;
	char	**env;
	char	**var_lst;
	char	*out_redir;
	int		outfd;
	char	*in_redir;
	int		infd;
	int		exit_code;
	bool	success;
	bool	append_mode;
}		t_mini;

// MAIN FUNCTIONS
t_tkn_lst	*process_input(char *line, t_mini *mini);
char		*get_next_token(char *line, int *q_type, t_mini *mini);
char		*handle_quote(t_mini *mini, int *q_type, int *index, char *line);
void		add_tkn_to_lst(t_tkn_lst **list_head, char *content, t_tkn token);

// HELPER FUNCTIONS
void		set_quote_type(int *q_type, char quote);
t_tkn		identify_token(char *token, int q_type);

// UTILS
bool		ft_isspace(char index);
char		*ft_strndup(char *s1, size_t len);
t_tkn_lst	*create_new_node(char *content, t_tkn token);
void		free_tkn_lst(t_tkn_lst *token_lst);
void		write_err(t_mini *minish, int code, char *arg);

#endif