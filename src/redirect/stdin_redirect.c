/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:51:35 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/10 15:38:04 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_infile(char *name)
{
	if (name)
	{
		if (access(name, F_OK) == -1 || access(name, R_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			close_all_fd();
			return (1);
		}
	}
	return (0);
}

int	adjust_hdoc(t_cmdlst *lst, int index)
{
	int	i;

	if (lst->here_docs)
	{
		i = 0;
		while (lst->here_docs[i])
		{
			index++;
			i++;
		}
	}
	return (index);
}

int	ft_redirect_here_doc(t_cmdlst *lst, t_data *data, int hdoc_index)
{
	int	fd;

	if (lst->here_docs)
	{
		fd = open(data->here_doc_name[hdoc_index], O_RDWR);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	ft_redirect_infile(t_cmdlst *lst)
{
	int	fd;
	int	i;

	if (lst->infiles)
	{
		i = 0;
		while (lst->infiles[i])
			i++;
		fd = open(lst->infiles[i - 1], O_RDONLY);
		if (fd < 0)
			fd = open(lst->infiles[i - 1], O_DIRECTORY);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	ft_redirect_stdin(t_cmdlst *lst, t_data *data, int i)
{
	int	res;

	res = 0;
	if (lst->stdin_last == 2)
		res = ft_redirect_here_doc(lst, data, i);
	else if (lst->stdin_last == 1)
		res = ft_redirect_infile(lst);
	return (res);
}
