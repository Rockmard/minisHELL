/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 07:50:10 by tpipi             #+#    #+#             */
/*   Updated: 2024/05/03 18:08:18 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_arg *arg, t_env **env)
{
	t_env	*tmp;

	if (arg)
		arg = arg->next;
	while (arg)
	{
		tmp = get_top_env(*env);
		while (tmp)
		{
			if (ft_strncmp(tmp->name, arg->val, ft_strlen(arg->val) + 1) == 0)
			{
				if (!tmp->prev)
					*env = (*env)->next;
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				multi_free_2char_and_ptr(tmp->name, tmp->val, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		arg = arg->next;
	}
	return (0);
}
