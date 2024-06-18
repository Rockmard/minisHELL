/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_char_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:17:31 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 20:19:08 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_get_envtab(t_env *env)
{
	char	**tab;
	char	*tmpjoin;
	int		i;

	tab = ft_calloc(sizeof(char *), (get_nb_env(env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->val)
		{
			tmpjoin = ft_strjoin(env->name, "=");
			if (!tmpjoin)
				return (free_char_tab(tab));
			tab[i] = ft_strjoin(tmpjoin, env->val);
			if (!tab[i])
				free(tmpjoin);
			if (!tab[i++])
				return (free_char_tab(tab));
			free(tmpjoin);
		}
		env = env->next;
	}
	return (tab);
}

char	**ft_get_argtab(t_arg *arg)
{
	char	**tab;
	int		i;

	if (!arg)
		return (NULL);
	tab = ft_calloc(sizeof(char *), get_nb_arg(arg) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (arg)
	{
		tab[i] = ft_strdup(arg->val);
		if (!tab[i++])
			return (free_char_tab(tab));
		arg = arg->next;
	}
	return (tab);
}
