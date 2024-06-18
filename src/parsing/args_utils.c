/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:35:04 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/10 16:11:45 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*ft_argnew(void *content)
{
	t_arg	*lst;

	lst = (t_arg *)malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->val = content;
	lst->next = NULL;
	return (lst);
}

t_arg	*ft_arglast(t_arg *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_argadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*last;

	if (*lst)
	{
		last = ft_arglast(*lst);
		last->next = &*new;
	}
	else
		*lst = new;
}

int	append_in_args(t_arg **args, char *op, char ***array, t_cmdlst *cmdlst)
{
	t_arg	*tmp;

	if (!(*args))
		return (1);
	if (ft_strlen(op) == ft_strlen((*args)->val)
		&& !strcmp_len((*args)->val, op))
	{
		if (ft_strncmp(op, "<", 2) == 0)
		{
			redirect_add(&cmdlst->redirect, 0, ft_strdup((*args)->next->val));
			cmdlst->stdin_last = 1;
		}
		else if (ft_strncmp(op, "<<", 2) == 0)
			cmdlst->stdin_last = 2;
		tmp = *args;
		*args = (*args)->next;
		arg_remove_one(&tmp, 1);
		tmp = *args;
		if (*args && !strarr_append(array, (*args)->val))
			return (0);
		*args = (*args)->next;
		arg_remove_one(&tmp, 1);
	}
	return (1);
}

int	arg_remove_one(t_arg **args, int free_val)
{
	t_arg	*tmp;

	if (!(*args))
		return (1);
	tmp = *args;
	*args = (*args)->next;
	if (free_val)
		free(tmp->val);
	free(tmp);
	tmp = NULL;
	return (1);
}
