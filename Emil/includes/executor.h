/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:56:58 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/03 15:17:33 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "parser.h"
# include "lexer.h"

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
void	free_env(t_minishell *minishell);
void	swap_vars(char **newenv);
void	replace_env(t_minishell *minishell, char *path);
char	*ft_getcwd(t_minishell *minishell);
char	*ft_getenv(t_minishell *minishell, char	*env);
char	**create_arg_lst(t_minishell *minishell);
char	*ft_check_var_lst(t_minishell *minishell, char *var);

#endif