/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:41:43 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/04 14:26:42 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

int	ft_env(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = get_top_env(env);
	while (tmp)
	{
		if (tmp->val)
		{
			ft_putstr_fd(tmp->name, fd);
			ft_printf("=", fd);
			ft_putendl_fd(tmp->val, fd);
		}
		tmp = tmp->next;
	}
	return (0);
}
