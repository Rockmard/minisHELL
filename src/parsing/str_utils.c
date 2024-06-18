/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:34:43 by nrontey           #+#    #+#             */
/*   Updated: 2024/05/15 08:04:48 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_r(char const *s1, char const *s2, char **to_free)
{
	char	*new_string;

	new_string = ft_strjoin(s1, s2);
	free(*to_free);
	*to_free = NULL;
	return (new_string);
}

int	free_str_tab(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free(array[i]);
		free(array);
	}
	return (0);
}

char	*ft_strldup(const char *s1, int size)
{
	int		s1_len;
	char	*dup;

	s1_len = ft_strlen(s1);
	if (s1_len > size)
		s1_len = size;
	dup = (char *)malloc((s1_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	dup[s1_len] = 0;
	while (--s1_len >= 0)
		dup[s1_len] = s1[s1_len];
	return (dup);
}

int	strarr_append(char ***array, char *str)
{
	char	**new;
	int		new_len;
	int		i;

	new_len = len_str_tab(*array) + 1;
	new = malloc(sizeof(char *) * (new_len + 1));
	if (!new)
		return (0);
	i = 0;
	while ((*array) && (*array)[i])
	{
		new[i] = ft_strdup((*array)[i]);
		if (!new[i])
			return (free_str_tab_n(new, i));
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (free_str_tab_n(new, i));
	i++;
	new[i] = 0;
	free_str_tab(*array);
	*array = new;
	return (1);
}

int	is_forbidden(char c)
{
	return (c == '\\' || c == ';' || c == '&');
}
