/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:35:30 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/10 15:42:58 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmdlst	*cmdlst_new(void)
{
	t_cmdlst	*new;

	new = malloc(sizeof(t_cmdlst));
	if (!new)
		return (0);
	new->cmd = NULL;
	new->next = NULL;
	new->todo = 0;
	new->args = NULL;
	new->infiles = NULL;
	new->outfiles = NULL;
	new->here_docs = NULL;
	new->stdin_last = 0;
	new->redirect = NULL;
	return (new);
}

int	cmdlst_append(t_cmdlst **new_lst, t_arg **args)
{
	(*new_lst)->cmd = ft_strdup((*args)->val);
	if (!(*new_lst)->cmd)
		return (0);
	if (!cmdlst_append_args(args, *new_lst))
		return (0);
	return (1);
}

int	create_cmd_lst(t_cmdlst **cmdlst, t_arg *args)
{
	t_cmdlst	*new_lst;

	*cmdlst = NULL;
	while (args && !get_arg_type(args->val))
	{
		new_lst = cmdlst_new();
		if (!new_lst)
			return (cmdlst_clear(cmdlst));
		if (*cmdlst)
			cmdlst_last(*cmdlst)->next = new_lst;
		else
			*cmdlst = new_lst;
		if (!cmdlst_append(&new_lst, &args))
			return (cmdlst_clear(cmdlst));
		if (args)
		{
			new_lst->todo = get_arg_type(args->val);
			arg_remove_one(&args, 1);
			continue ;
		}
		if (args)
			args = args->next;
	}
	return (1);
}

t_cmdlst	*cmdlst_last(t_cmdlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

int	cmdlst_append_args(t_arg **args, t_cmdlst *new)
{
	t_arg	*prev_arg;

	prev_arg = NULL;
	while (*args && !get_arg_type((*args)->val))
	{
		if (!append_out_args(args, ">", &(new->outfiles), new))
			return (0);
		else if (!append_in_args(args, "<", &(new->infiles), new))
			return (0);
		else if (!append_out_args(args, ">>", &(new->outfiles), new))
			return (0);
		else if (!append_in_args(args, "<<", &(new->here_docs), new))
			return (0);
		if ((*args) && !is_sep((*args)->val))
		{
			if (!lst_append(&(new->args), (*args)->val))
				return (0);
			prev_arg = *args;
			*args = (*args)->next;
			free(prev_arg);
		}
	}
	return (1);
}
