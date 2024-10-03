/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:48:37 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/02 18:19:55 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

//============ HEADER FILES =============
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 	0
# define EXIT_FAILURE 	1

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000
#endif

// STRUCT's
/* === comand === */
/* contains info of the comand
*/

//=========== STRUCTS =====================

typedef enum {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_RIDIRECTION,
	TOKEN_UNKNOWN 	
}	token_type;

/*
	COMMAND STRUCT
*/
typedef struct s_comands
{
    char    *cmd; // this is going to store the comand name
    char    **args; // arguments of the comands
	int		input_redir; // FD for input rederections
	int		output_redir;// FD for output rederections
    struct s_comand *next;
}   t_comands;

/*
	LEXER STRUCT
*/
typedef struct s_lexer
{
	char		*input; // the original input 
	t_comands	*comands; // pointer to the commands => STRUCT
	int			n_of_cmd; // Number of commands
}	t_lexer;

/*
	TOKEN STRUCT
*/
typedef struct s_token
{
	char		*data;
	token_type	type;
	struct s_token *next;
}	t_token;





/* === MINISHELL STRUCT ===*/
/*
*** This struct is going to contain every information if minishell data
*** comand info , comand table
*** input information.
*/
typedef struct s_msh
{
	char **env;
	char *input;
}	t_msh;

//loop
void prompt(t_msh *msh);

//enviroment
char **create_env(char **envp);
void free_env(t_msh *msh);

// LEXING 
int is_this(char c);

token_type get_token_type(char c);

t_token *create_tok(char *data, token_type type);


#endif