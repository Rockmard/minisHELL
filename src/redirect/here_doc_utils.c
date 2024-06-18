/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:55:10 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/04 01:17:56 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_randoname(char *base_name)
{
	char	*randonum;
	char	*randoname;
	int		i;

	i = 0;
	while (1)
	{
		randonum = ft_itoa(i);
		if (!randonum)
			return (NULL);
		randoname = ft_strjoin(base_name, randonum);
		free(randonum);
		if (!randoname)
			return (NULL);
		if (access(randoname, F_OK) == -1 && access(randoname, W_OK) == -1)
			break ;
		i++;
		free(randoname);
	}
	return (randoname);
}

int	ft_create_here_doc_name(t_cmdlst *lst, t_data *data)
{
	t_cmdlst	*tmp;
	int			i;
	int			j;

	i = 0;
	tmp = lst;
	data->here_doc_name = ft_calloc(get_nb_here_doc(lst) + 1, sizeof(char *));
	while (tmp)
	{
		j = 0;
		while (tmp->here_docs && tmp->here_docs[j])
		{
			data->here_doc_name[i] = ft_get_randoname("/tmp/here_doc");
			if (!data->here_doc_name[i])
				return (1);
			close(open(data->here_doc_name[i], O_CREAT, S_IRWXU));
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	buff_error(int fd, int fd_hdoc, t_data *data, char *delimiter)
{
	if (read(0, NULL, 0) == -1)
	{
		dup2(fd, 0);
		close(fd);
		close(fd_hdoc);
		data->return_val = 130;
		return (1);
	}
	else
	{
		dup2(fd, 0);
		ft_putstr_fd("minishell: warning: here-document", 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putendl_fd("')", 2);
		return (0);
	}
}

void	clear_here_doc(t_data *data)
{
	int	i;

	i = 0;
	while (data->here_doc_name && data->here_doc_name[i])
	{
		unlink(data->here_doc_name[i]);
		i++;
	}
	free_char_tab(data->here_doc_name);
}
