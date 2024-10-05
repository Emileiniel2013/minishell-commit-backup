/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:32:53 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/05 13:32:35 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "lexer.h"
# include <stdbool.h>

typedef struct	t_simple_command
{
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
}		t_command_table;

typedef struct t_minishell
{
	t_command_table	*table;
	char			**env;
	char			**var_lst;
}		t_minishell;

char		**copy_env(char **envp);
t_minishell	*init_mini_vars(char *envp[]);

#endif