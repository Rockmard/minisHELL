/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:33:24 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/10 15:47:20 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arg_clear(t_arg **arg)
{
	t_arg	*next;

	while (*arg)
	{
		next = (*arg)->next;
		free((*arg)->val);
		free(*arg);
		*arg = next;
	}
	*arg = NULL;
	return (0);
}

int	outlst_clear(t_outlst **lst)
{
	t_outlst	*next;

	while (*lst)
	{
		next = (*lst)->todo;
		free((*lst)->filename);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return (0);
}

int	cmdlst_clear(t_cmdlst **lst)
{
	t_cmdlst	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->cmd);
		arg_clear(&(*lst)->args);
		outlst_clear(&(*lst)->outfiles);
		free_str_tab((*lst)->infiles);
		free_str_tab((*lst)->here_docs);
		redirect_clear(&(*lst)->redirect);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return (0);
}

int	free_str_tab_n(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
	return (0);
}

int	free_str(char *str)
{
	free(str);
	return (0);
}
