/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_of.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:46:29 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 19:35:21 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	index_of_newline(char *str)
{
	int	i;
	int	tmp;

	if (str[0] == '\0')
		return (0);
	i = index_of(str, " ", 1);
	tmp = index_of(str, "\t", 1);
	if (tmp || str[0] == '\t')
		if (tmp < i)
			i = tmp;
	return (i);
}

int	index_of(char *str, char *search, int n)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strncmp(str + i, search, ft_strlen(search)) == 0)
			n--;
		if (n <= 0)
			return (i);
		i++;
	}
	return (i);
}

void	remove_empty_command(t_cmdlst *tmp)
{
	while (ft_strlen(tmp->cmd) == 0)
	{
		arg_remove_one(&tmp->args, 1);
		free(tmp->cmd);
		if (tmp->args)
			tmp->cmd = ft_strdup(tmp->args->val);
		else
		{
			tmp->cmd = NULL;
			break ;
		}
	}
	if (ft_strncmp("\b", tmp->cmd, 1) == 0)
	{
		free(tmp->cmd);
		tmp->cmd = ft_strdup("");
	}
}
