/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:56:58 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/30 17:20:00 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "lexer.h"
# include "parser.h"
# include <limits.h>


void		executor(t_mini *mini);
void		handle_echo(t_mini *mini);
void		handle_pwd(t_mini *mini);
void		handle_cd(t_mini *mini);
void		handle_env(t_mini *mini);
void		handle_export(t_mini *mini);
void		handle_unset(t_mini *mini);
void        handle_exit(t_mini *mini);
void		execute_file(t_mini *mini);
void		check_path(t_mini *mini);
char		**list2array(t_mini *mini);
void		free_arr(char **arr);
void		swap_vars(char **newenv);
void		replace_env(t_mini *mini, char *path, char *env);
char		*ft_getcwd(t_mini *mini);
char		**create_arg_lst(t_mini *mini);
char		*ft_check_var_lst(t_mini *mini, char *var);
void		add_var_to_list(t_mini *mini);
void    	mini_main(t_mini *mini);
int			handle_redirections(t_mini *mini);
void		restore_redirections(t_mini *mini);
t_mini		*init_mini_vars(int argc, char **argv, char **envp);
bool		ft_isnumber(char *content);
void		free_mini(t_mini *mini, bool keep_env);
void        sigint_handler(int sig);
void	    handle_signals(void);
int         check_existing_var(char *newvar, t_mini *mini);
void    	handle_shlvl(t_mini *mini, char sign);
bool	    check_nl(char *content);
bool		check_builtin(t_mini *minish);

#endif
