/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:44:24 by tpipi             #+#    #+#             */
/*   Updated: 2024/05/03 18:08:20 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	*free_env_struct(t_env *env)
{
	if (env)
	{
		free_env_struct(env->next);
		free(env->name);
		free(env->val);
		free(env);
	}
	return (NULL);
}

void	*free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	*multi_free_2char_and_ptr(char *str1, char *str2, void *ptr)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (ptr)
		free(ptr);
	return (NULL);
}
