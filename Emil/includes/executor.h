/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:56:58 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/25 18:54:22 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "lexer.h"
# include "parser.h"
# include <limits.h>

void		executor(t_minishell *minishell);
void		handle_echo(t_minishell *minishell);
void		handle_pwd(t_minishell *minishell);
void		handle_cd(t_minishell *minishell);
void		handle_env(t_minishell *minishell);
void		handle_export(t_minishell *minishell);
void		handle_unset(t_minishell *minishell);
void        handle_exit(t_minishell *minishell);
void		execute_file(t_minishell *minishell);
void		check_path(t_minishell *minishell);
char		**list2array(t_minishell *minishell);
void		free_arr(char **arr);
void		swap_vars(char **newenv);
void		replace_env(t_minishell *minishell, char *path);
char		*ft_getcwd(t_minishell *minishell);
char		**create_arg_lst(t_minishell *minishell);
char		*ft_check_var_lst(t_minishell *minishell, char *var);
void		add_var_to_list(t_minishell *minishell);
void    	mini_main(t_minishell *minishell);
int			handle_redirections(t_minishell *minishell);
void		restore_redirections(t_minishell *minishell);
t_minishell	*init_mini_vars(int argc, char **argv, char **envp);
bool		ft_isnumber(char *content);
void		free_minishell(t_minishell *minishell, bool keep_env);
void        sigint_handler(int sig);
void	    handle_signals(void);
int         check_existing_var(char *newvar, t_minishell *minishell);

#endif
