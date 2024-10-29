/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/29 12:39:34 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	set_q_type(int *quote_type, char quote)
{
	if (quote == '"')
		*quote_type = 2;
	else if (quote == '\'')
		*quote_type = 1;
}

t_token	identify_token(char *token, int quote_type)
{
	if (quote_type == 1)
		return (SINGLE_QUOTE);
	else if (quote_type == 2)
		return (DOUBLE_QUOTE);
	else if (ft_strncmp(token, "|", ft_strlen(token)) == 0)
		return (PIPE);
	else if (ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (REDIRECT_IN);
	else if (ft_strncmp(token, ">", ft_strlen(token)) == 0)
		return (REDIRECT_OUT);
	else if (ft_strncmp(token, ">>", ft_strlen(token)) == 0)
		return (REDIRECT_OUT_APPEND);
	else if (ft_strncmp(token, "<<", ft_strlen(token)) == 0)
		return (HEREDOC);
	else
		return (STRING);
}
