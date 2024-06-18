/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:05:28 by tpipi             #+#    #+#             */
/*   Updated: 2024/04/22 19:30:08 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env_utils.h"

t_env	*get_top_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

t_env	*get_bot_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_env	*get_t_env(char **env)
{
	int		i;
	char	*name;
	char	*val;
	t_env	*env_struct;

	i = 0;
	env_struct = NULL;
	while (env && env[i])
	{
		name = ft_strndup(env[i], get_egal_index(env[i]));
		if (!name)
			return (free_env_struct(get_top_env(env_struct)));
		val = get_val(env[i]);
		env_struct = add_env(name, val, env_struct);
		if (!env_struct)
			return (free_env_struct(get_top_env(env_struct)));
		if (env_struct->next)
			env_struct = env_struct->next;
		i++;
	}
	return (get_top_env(env_struct));
}

t_env	*ft_copy_env(t_env *env)
{
	t_env	*copy;
	char	*name;
	char	*val;

	copy = NULL;
	while (env)
	{
		val = NULL;
		name = ft_strdup(env->name);
		if (!name)
			return (free_env_struct(get_top_env(copy)));
		if (env->val)
			val = ft_strdup(env->val);
		copy = add_env(name, val, copy);
		if (!copy)
			return (free_env_struct(get_top_env(copy)));
		if (copy->next)
			copy = copy->next;
		env = env->next;
	}
	return (get_top_env(copy));
}
