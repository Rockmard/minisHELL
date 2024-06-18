/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:34:57 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 20:30:28 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/struct.h"

unsigned int	get_nb_arg(t_arg *arg)
{
	unsigned int	cpt;
	t_arg			*temp;

	temp = arg;
	if (!temp)
		return (0);
	cpt = 0;
	while (temp)
	{
		cpt++;
		temp = temp->next;
	}
	return (cpt);
}

unsigned int	get_nb_env(t_env *env)
{
	unsigned int	cpt;
	t_env			*temp;

	temp = env;
	if (!temp)
		return (0);
	cpt = 0;
	while (temp)
	{
		if (temp->val)
			cpt++;
		temp = temp->next;
	}
	return (cpt);
}

unsigned int	get_nb_cmd(t_cmdlst *lst)
{
	unsigned int	cpt;
	t_cmdlst		*temp;

	temp = lst;
	if (!temp)
		return (0);
	cpt = 0;
	while (temp)
	{
		cpt++;
		if (!temp->next && !temp->args)
			cpt--;
		if (temp->todo != 1)
			break ;
		temp = temp->next;
	}
	return (cpt);
}

unsigned int	get_nb_here_doc(t_cmdlst *lst)
{
	unsigned int	cpt;
	unsigned int	i;
	t_cmdlst		*temp;

	temp = lst;
	cpt = 0;
	while (temp)
	{
		i = 0;
		while (temp->here_docs && temp->here_docs[i])
		{
			cpt++;
			i++;
		}
		temp = temp->next;
	}
	return (cpt);
}
