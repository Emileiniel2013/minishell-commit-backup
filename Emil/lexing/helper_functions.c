/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/29 13:38:29 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	set_quote_type(int *quote_type, char quote)
{
	if (quote == '"')
		*quote_type = 2;
	else if (quote == '\'')
		*quote_type = 1;
}

t_tkn	identify_token(char *token, int quote_type)
{
	if (quote_type == 1)
		return (SINGLE_QUOTE);
	else if (quote_type == 2)
		return (DOUBLE_QUOTE);
	else if (ft_strncmp(token, "|", ft_strlen(token)) == 0)
		return (PIPE);
	else if (ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (REDIRIN);
	else if (ft_strncmp(token, ">", ft_strlen(token)) == 0)
		return (REDIROUT);
	else if (ft_strncmp(token, ">>", ft_strlen(token)) == 0)
		return (REDIROUTAPP);
	else if (ft_strncmp(token, "<<", ft_strlen(token)) == 0)
		return (HEREDOC);
	else
		return (STRING);
}
