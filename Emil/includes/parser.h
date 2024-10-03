/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:27:42 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/03 15:00:49 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_FILENAME,
	TOKEN_ARGUMENT,
	TOKEN_LITERAL,
	TOKEN_OPERATOR,
	TOKEN_SPECIAL,
	TOKEN_INVALID_ARG,
	TOKEN_UNKNOWN
}	token_type;

typedef struct	t_simple_command
{
	token_type					token;
	char						*content;
	struct	t_simple_command	*next;
}	t_command;

void		process_input(char *line);

#endif