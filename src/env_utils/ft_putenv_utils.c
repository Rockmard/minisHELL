/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:10:44 by tpipi             #+#    #+#             */
/*   Updated: 2024/04/22 19:30:26 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env_utils.h"

int	get_egal_index(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strndup(char *str, int i)
{
	int		j;
	char	*dup;

	if (!str)
		return (NULL);
	if (i < 0)
		return (ft_strdup(str));
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	j = 0;
	while (str[j] && j < i)
	{
		dup[j] = str[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

t_env	*add_env(char *name, char *val, t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(name);
		free(val);
		return (NULL);
	}
	new->name = name;
	new->val = val;
	new->prev = env;
	new->next = NULL;
	if (env)
		env->next = new;
	return (new);
}

char	*get_val(char *str)
{
	if (get_egal_index(str) < 0)
		return (NULL);
	else if (!str[get_egal_index(str) + 1])
		return (ft_strdup(""));
	else
		return (ft_strdup(str + get_egal_index(str) + 1));
}
