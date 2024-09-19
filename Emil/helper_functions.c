/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:36:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/19 15:46:09 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/executor.h"

void	replace_env(command_table *table, char *path)
{
	int		i;
	size_t	size;

	i = 0;
	while (table->envp[i] != NULL)
	{
		size = ft_strlen(table->envp[i]);
		if (ft_strnstr(table->envp[i], "PWD=/", size) != NULL)
			break;
		i++;
	}
	free(table->envp[i]);
	table->envp[i] = malloc(sizeof(char) * ft_strlen(path) + 4);
	table->envp[i] = ft_strjoin("PWD=", path);
	printf("%s\n", table->envp[i]);
}
