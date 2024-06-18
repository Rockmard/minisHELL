/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:09:33 by tpipi             #+#    #+#             */
/*   Updated: 2024/05/27 16:27:55 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env_utils.h"

static t_env	*change_val(t_env *env, char *name, char *val)
{
	t_env	*tmp;

	tmp = get_top_env(env);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
		{
			if (val)
			{
				free(tmp->val);
				tmp->val = val;
			}
			free(name);
			break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

int	ft_putenv(char *str, t_env **env)
{
	int		i;
	char	*name;
	char	*val;
	t_env	*tmp;

	i = get_egal_index(str);
	name = ft_strndup(str, i);
	if (!name)
		return (1);
	val = get_val(str);
	tmp = change_val(*env, name, val);
	if (!tmp)
	{
		*env = get_bot_env(*env);
		*env = add_env(name, val, *env);
		if (!(*env))
			return (1);
		if ((*env)->next)
			*env = (*env)->next;
	}
	*env = get_top_env(*env);
	return (0);
}
