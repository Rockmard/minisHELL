/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:13:46 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/10 18:52:11 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmdlst	*adjust_cmdlst(t_cmdlst *lst, int *j)
{
	if (lst && (!lst->here_docs || !lst->here_docs[*j]))
	{
		lst = lst->next;
		*j = 0;
	}
	while (lst && !lst->here_docs)
	{
		lst = lst->next;
		if (!lst)
			break ;
	}
	return (lst);
}

static void	proper_write(char *buffer, int fd_hdoc, t_data *data, \
			char *delimiter)
{
	char	*parsed_buffer;

	parsed_buffer = ft_parse_buffer(buffer, delimiter, data);
	ft_putendl_fd(parsed_buffer, fd_hdoc);
	free(buffer);
	free(parsed_buffer);
}

static int	ft_fill_here_doc(t_data *data, t_hdoc_info *hdoc_info)
{
	char	*buffer;

	while (1)
	{
		if (access(hdoc_info->path, F_OK) == -1 || \
		access(hdoc_info->path, W_OK) == -1)
		{
			close(hdoc_info->fd_stdin);
			close(hdoc_info->fd_hdoc);
			return (255);
		}
		buffer = readline("> ");
		if (!buffer)
		{
			if (buff_error(hdoc_info->fd_stdin, hdoc_info->fd_hdoc, \
			data, hdoc_info->delimiter))
				return (130);
			else
				break ;
		}
		if (ft_check_heredoc(buffer, hdoc_info->delimiter) == 1)
			break ;
		proper_write(buffer, hdoc_info->fd_hdoc, data, hdoc_info->delimiter);
	}
	return (0);
}

static int	ft_create_here_doc(t_data *data, t_cmdlst *tmp)
{
	int			i;
	int			j;
	int			res;
	t_hdoc_info	hdoc_info;

	i = 0;
	j = 0;
	while (data->here_doc_name && data->here_doc_name[i])
	{
		hdoc_info.fd_hdoc = open(data->here_doc_name[i], O_RDWR);
		if (hdoc_info.fd_hdoc < 0)
			return (255);
		hdoc_info.fd_stdin = dup(0);
		tmp = adjust_cmdlst(tmp, &j);
		hdoc_info.path = data->here_doc_name[i];
		hdoc_info.delimiter = tmp->here_docs[j];
		res = ft_fill_here_doc(data, &hdoc_info);
		if (res != 0)
			return (res);
		i++;
		j++;
		close(hdoc_info.fd_stdin);
		close(hdoc_info.fd_hdoc);
	}
	return (0);
}

int	ft_here_doc(t_cmdlst *cmdlst, t_data *data)
{
	t_cmdlst	*tmp;

	tmp = cmdlst;
	signal(SIGINT, heredoc_kill_handler);
	if (!access("/tmp", F_OK) && !access("/tmp", W_OK) \
	&& !access("/tmp", R_OK))
	{
		if (ft_create_here_doc_name(cmdlst, data))
			return (255);
		return (ft_create_here_doc(data, tmp));
	}
	return (0);
}
