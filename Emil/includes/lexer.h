/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:27:42 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/26 18:18:20 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

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

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_FILENAME,
	TOKEN_ARGUMENT,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_OUT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_DELIMITER,
	TOKEN_STRING,
	TOKEN_UNKNOWN
}	token_type;


typedef struct t_tokenizer
{
	char				*content;
	token_type			token;
	struct t_tokenizer	*next;
}		t_tokens;

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
	t_command					*cmd_head;
	struct t_test_struct		*next;
}		t_command_table;

typedef struct t_minishell
{
	t_command_table	*table;
	t_command_table *table_head;
	char			**env;
	char			**var_lst;
	char			*out_redir;
	int				outfd;
	char			*in_redir;
	int				infd;
	int				exit_code;
	bool			success;
	bool			append_mode;
}		t_minishell;

t_tokens	*process_input(char *line, t_minishell *minishell);
bool    	ft_isspace(char index);
char    	*get_next_token(char *line, int *quote_type, t_minishell *minishell);
char		*ft_strndup(char *s1, size_t len);
void		set_quote_type(int *quote_type, char quote);
token_type	identify_token(char *token, int quote_type);
void		add_token_to_lst(t_tokens **list_head,char *content, token_type token);
t_tokens	*create_new_node(char *content, token_type token);
void		free_token_lst(t_tokens *token_lst);
char		*print_token(token_type token);

#endif