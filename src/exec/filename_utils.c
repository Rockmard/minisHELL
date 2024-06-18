/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:19:20 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/11 12:55:49 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strddup(char *str, int i, int j)
{
	char	*dup;
	int		l;

	if (!str)
		return (NULL);
	if (i == -1)
		return (ft_strdup(str));
	dup = ft_calloc(sizeof(char), (i - j + 1));
	if (!dup)
		return (NULL);
	l = 0;
	while (str[j] && j < i)
	{
		dup[l] = str[j];
		j++;
		l++;
	}
	return (dup);
}

char	*ft_get_full_path(char *folder, char *file)
{
	char		*full_path;
	char		*tmpjoin;

	if (!folder || !file)
		return (NULL);
	tmpjoin = ft_strjoin(folder, "/");
	if (!tmpjoin)
		return (NULL);
	full_path = ft_strjoin(tmpjoin, file);
	free(tmpjoin);
	if (!full_path)
		return (NULL);
	return (full_path);
}

void	ft_print_err_file(char *msg, char *file)
{
	if (msg && file)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(msg, 2);
	}
}
