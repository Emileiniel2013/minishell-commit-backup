/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:32:53 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/29 12:31:52 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "lexer.h"
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

char	**copy_env(char **envp);
void	parse_input(char *line, t_mini *minish);
void	expand_env_vars(char **content, t_mini *minish);
char	*ft_getenv(t_mini *minish, char	*env);
char	*check_string(char **content, t_mini *minish);
int		check_valid_redir_input(t_tkn_lst **token_lst, t_mini *minish);
int		check_valid_pipe(t_tkn_lst *token_lst, t_table *table, t_mini *minish);
void	add_token_to_table(t_table **table, t_tkn_lst *token_lst);
void	add_cmd_node(t_cmd **cmd, char *content);
bool    check_builtin(t_mini *minish);
int		handle_heredoc(t_tkn_lst **token_lst, t_mini *minish);
void	free_table(t_mini *minish);
void	free_cmd(t_cmd *cmd);
int    	ft_strcmp(char *s1, char *s2);

#endif