/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_getter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:38:27 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 01:34:17 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_file_a_cmd(char *folder, char *file, int *res, char **f)
{
	char		*filename;

	filename = ft_get_full_path(folder, file);
	*f = NULL;
	if (!filename)
		return (1);
	free(folder);
	if (access(filename, F_OK) == 0 && closedir(opendir(filename)) == -1)
	{
		if (access(filename, X_OK) == -1)
		{
			ft_print_err_file(": Permission denied\n", filename);
			*res = 126;
		}
		else
			*f = filename;
		return (1);
	}
	free(filename);
	return (0);
}

static char	*ft_check_path(char *file, char *path, int *res)
{
	int		i;
	int		j;
	char	*folder;
	char	*filename;

	i = 0;
	filename = NULL;
	while (path)
	{
		j = i;
		while (path[i] && path[i] != ':')
			i++;
		folder = ft_strddup(path, i, j);
		if (!folder)
			return (NULL);
		if (is_file_a_cmd(folder, file, res, &filename))
			return (filename);
		if (!path[i])
			break ;
		i++;
	}
	return (NULL);
}

static char	*ft_check_relative_path(char *file, int *res)
{
	char	*full_path;

	if (!closedir(opendir(file)))
	{
		*res = 126;
		ft_print_err_file(": Is a directory\n", file);
	}
	else if (access(file, F_OK))
	{
		*res = 127;
		ft_print_err_file(": No such file or directory\n", file);
	}
	else if (access(file, X_OK))
	{
		*res = 126;
		ft_print_err_file(": Permission denied\n", file);
	}
	else
	{
		full_path = ft_strdup(file);
		if (!full_path)
			return (NULL);
		return (full_path);
	}
	return (NULL);
}

char	*ft_get_filename(char *file, char *path, int *res)
{
	int		is_path;
	char	*full_path;

	if (is_a_built_in(file))
		return (NULL);
	if (file[0] && file[0] == '.' && !file[1])
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		*res = 2;
		return (NULL);
	}
	is_path = !(!ft_strchr(file, '/'));
	if (is_path || !path)
		full_path = ft_check_relative_path(file, res);
	else
	{
		full_path = ft_check_path(file, path, res);
		if (!full_path && *res != 126)
		{
			*res = 127;
			ft_print_err_file(": command not found\n", file);
		}
	}
	return (full_path);
}
