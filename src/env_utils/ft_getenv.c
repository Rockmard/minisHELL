/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:08:25 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/10 17:21:46 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env_utils.h"

char	*ft_getenv(char *key, t_env *env)
{
	env = get_top_env(env);
	while (env && key)
	{
		if (ft_strncmp(key, env->name, ft_strlen(key) + 1) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

int	does_key_exist(char *key, t_env *env)
{
	env = get_top_env(env);
	while (env && key)
	{
		if (ft_strncmp(key, env->name, ft_strlen(key) + 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
