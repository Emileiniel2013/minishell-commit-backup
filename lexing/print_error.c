/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:44:09 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/30 21:10:19 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	write_err(t_mini *minish, int code, char *arg)
{
	if (!arg)
		write_simple_err(code);
	else
	{
		if (code == 9 || code == 14 || code == 11 || code == 12)
		{
			write(STDERR_FILENO, "Minishell: syntax error ", 24);
			write(STDERR_FILENO, "near unexpected token `", 23);
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, "'\n", 2);
		}
		else if (code == 2 || code == 4 || code == 5)
		{
			write(STDERR_FILENO, "Minishell: cd: ", 15);
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
		}
		else
			write_arg_err(code, arg);
	}
	minish->exit_code = code;
	minish->success = false;
}

void	write_simple_err(int code)
{
	if (code == 16)
	{
		write(STDERR_FILENO, "Minishell: synthax error: u", 27);
		write(STDERR_FILENO, "nmatched quote character\n", 26);
	}
	else if (code == 8 || code == 13 || code == 10)
	{
		write(STDERR_FILENO, "Minishell: syntax error near ", 29);
		write(STDERR_FILENO, "unexpected token `newline'\n", 28);
	}
	else if (code == 15)
	{
		write(STDERR_FILENO, "Minishell: Failed to ", 21);
		write(STDERR_FILENO, "create heredoc file\n", 21);
	}
	else if (code == 1 || code == 3)
		write(STDERR_FILENO, "Minishell: cd: HOME not set\n", 29);
	else if (code == 21)
		write(STDERR_FILENO, "Minishell: cd: OLDPWD not set\n", 31);
	else if (code == 17)
		write(STDERR_FILENO, "Minishell: exit: too many arguments\n", 36);
	else if (code == 7)
		write(STDERR_FILENO, "Minishell: Error opening output file\n", 38);
	else if (code == 29)
		write(STDERR_FILENO, "Minishell: ./: is a directory\n", 31);
}

void	write_arg_err(int code, char *arg)
{
	if (code == 18)
	{
		write(STDERR_FILENO, "Minishell: exit: ", 17);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": numeric argument required\n", 29);
	}
	else if (code == 22 || code == 6)
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
	}
	else if (code == 23 || code == 24 || code == 35 || code == 36)
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": command not found\n", 21);
	}
}
