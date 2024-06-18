/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:36:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/10 16:09:59 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_outlst	*outlst_new(char *filename, int action)
{
	t_outlst	*new;

	new = malloc(sizeof(t_outlst));
	if (!new)
		return (0);
	new->filename = ft_strdup(filename);
	if (!new->filename)
	{
		free(new);
		return (0);
	}
	new->action = action;
	new->todo = NULL;
	return (new);
}

int	outlst_append(t_outlst **lst, char *filename, char *special)
{
	t_outlst	*new;
	int			action;

	action = 0;
	if (ft_strlen(special) == 2)
		action = 1;
	new = outlst_new(filename, action);
	if (!new)
		return (0);
	if (*lst)
		outlst_last(*lst)->todo = new;
	else
		(*lst) = new;
	return (1);
}

int	append_out_args(t_arg **args, char *op, t_outlst **out, t_cmdlst *cmdlst)
{
	t_arg	*tmp;

	if (!(*args))
		return (1);
	if (ft_strlen(op) == ft_strlen((*args)->val)
		&& !strcmp_len((*args)->val, op))
	{
		if (ft_strncmp(op, ">", 2) == 0)
			redirect_add(&cmdlst->redirect, 1, ft_strdup((*args)->next->val));
		else if (ft_strncmp(op, ">>", 2) == 0)
			redirect_add(&cmdlst->redirect, 2, ft_strdup((*args)->next->val));
		tmp = *args;
		*args = (*args)->next;
		arg_remove_one(&tmp, 1);
		tmp = *args;
		if (*args && !outlst_append(out, (*args)->val, op))
			return (0);
		*args = (*args)->next;
		arg_remove_one(&tmp, 1);
	}
	return (1);
}

t_outlst	*outlst_last(t_outlst *lst)
{
	if (lst)
		while (lst->todo)
			lst = lst->todo;
	return (lst);
}
