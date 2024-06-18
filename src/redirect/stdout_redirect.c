/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 03:46:42 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/10 16:39:15 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_open_check(char *filename, int type)
{
	int	fd;

	fd = -1;
	if (type == 1)
		fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (type == 2)
		fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	return (fd);
}

int	check_outfile(char *name, int type)
{
	int			fd;

	if (name)
	{
		fd = ft_open_check(name, type);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	ft_redirect_outfile(t_cmdlst *lst)
{
	t_outlst	*out;
	int			fd;

	out = lst->outfiles;
	if (out)
	{
		while (out->todo)
			out = out->todo;
		fd = ft_open_check(out->filename, out->action + 1);
		if (fd < 0)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	ft_get_stdout_fd(t_cmdlst *lst)
{
	t_outlst	*out;
	int			fd;

	out = lst->outfiles;
	if (out)
	{
		while (out->todo)
			out = out->todo;
		fd = ft_open_check(out->filename, out->action + 1);
		if (fd < 0)
			return (2);
		return (fd);
	}
	return (1);
}
