/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:56:58 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/07 17:08:27 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "lexer.h"
# include "parser.h"
# include <limits.h>

// EXECUTOR
void	mini_main(t_mini *minish);
void	child_execution(t_mini *minish, int prevpipefd, int *pipefd);
void	executor(t_mini *minish);
void	parent_execution(t_mini *minish, int pid);
void	execute_file(t_mini *minish);

// BUILTINS
void	handle_echo(t_mini *minish);
void	handle_pwd(t_mini *minish);
void	handle_cd(t_mini *minish);
void	handle_env(t_mini *minish);
void	handle_export(t_mini *minish);
void	handle_unset(t_mini *minish);
void	handle_exit(t_mini *minish);
void	check_path(t_mini *minish);
bool	check_builtin(t_mini *minish);
void	execute_path(t_mini *minish, char *path);

// BUILTINS UTILS
char	*ft_getcwd(t_mini *minish);
int		handle_cd_home(t_mini *minish, char *path);
int		handle_cd_oldpwd(t_mini *minish);
char	*check_valid_cmd(char **paths, t_mini *minish);

// ENV MANIPULATION
void	add_new_var_to_arr(char *newvar, t_mini *minish);
char	*ft_check_var_lst(t_mini *minish, char *var);
void	replace_env(t_mini *minish, char *path, char *env);
void	add_var_to_list(t_mini *minish);
char	*append_var(char *newvar, char *env);
bool	srch_and_rplc_env(char *env, char *newvar, t_mini *minish, bool join);
void	handle_shlvl(t_mini *minish, char sign);
void	unset_var(t_mini *minish, int i);
void	swap_vars(char **newenv);
bool	ft_isnumber(char *content);

// INITIALIZATION/REDIR
t_mini	*init_mini_vars(int argc, char **argv, char **envp);
int		handle_redirections(t_mini *minish);
void	restore_redirections(t_mini *minish);

// SIGNAL HANDLING
void	handle_signals(void);
void	sigint_handler(int sig);

// HELPER FUNCTIONS
int		check_existing_env(t_mini *minish, bool *found_env, char *env);
int		check_existing_var(char *newvar, t_mini *minish);
char	*check_append_mode(char *newvar, int i, bool *join);
char	**list2array(t_mini *minish);
bool	check_nl(char *content);

// CLEANUP
void	ft_free(char **content);
void	free_arr(char **arr);
void	free_minish(t_mini *minish, bool keep_env);

#endif
