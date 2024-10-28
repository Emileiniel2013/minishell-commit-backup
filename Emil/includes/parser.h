/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:32:53 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/28 15:32:06 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "lexer.h"
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

char	**copy_env(char **envp);
void	parse_input(char *line, t_minishell *minishell);
void	expand_env_vars(char **content, t_minishell *minishell);
char	*ft_getenv(t_minishell *minishell, char	*env);
char	*check_string(char **content, t_minishell *minishell);
int		check_valid_redir_input(t_tokens **token_lst, t_minishell *minishell);
int		check_valid_pipe(t_tokens *token_lst, t_command_table *table, t_minishell *minishell);
void	add_token_to_table(t_command_table **table, t_tokens *token_lst);
void	add_cmd_node(t_command **cmd, char *content);
bool    check_builtin(t_minishell *minishell);
int		handle_heredoc(t_tokens **token_lst, t_minishell *minishell);
void	free_table(t_minishell *minishell);
void	free_cmd(t_command *cmd);
int    	ft_strcmp(char *s1, char *s2);

#endif