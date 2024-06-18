/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:22:26 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/10 17:14:56 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->type = 0;
	redirect->name = NULL;
	redirect->next = NULL;
	return (redirect);
}

int	redirect_clear(t_redirect **redirect)
{
	t_redirect	*tmp;

	while (*redirect)
	{
		tmp = (*redirect)->next;
		if ((*redirect)->name)
			free((*redirect)->name);
		free(*redirect);
		*redirect = tmp;
	}
	return (0);
}

int	redirect_add(t_redirect **redirect, int type, char *name)
{
	t_redirect	*new;
	t_redirect	*tmp;

	new = init_redirect();
	if (!new)
		return (0);
	new->type = type;
	new->name = name;
	if (!*redirect)
		*redirect = new;
	else
	{
		tmp = *redirect;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}
