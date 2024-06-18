/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:26:13 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 20:13:24 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pipex(t_cmdlst *cmdlst, t_data *data, int fd[2][2], int nb_cmd)
{
	int				i;
	t_cmdlst		*tmp;

	tmp = cmdlst;
	i = 0;
	data->hdoc_index = -1;
	while (i < nb_cmd)
	{
		data->hdoc_index = adjust_hdoc(cmdlst, data->hdoc_index);
		data->pack->pid[i] = fork();
		if (data->pack->pid[i] < 0)
			return (1);
		if (data->pack->pid[i] == 0)
		{
			reset_signals();
			ft_pipes_exchange(i, nb_cmd, fd);
			ft_execute_command(cmdlst, data, tmp);
		}
		re_pipe(i % 2, fd);
		ft_usleep(1);
		i++;
		cmdlst = cmdlst->next;
	}
	ft_end_pipes(nb_cmd, data->pack, &data->return_val);
	return (0);
}

int	ft_treat_nb_cmd(t_cmdlst *cmdlst, t_data *data, int fd[2][2], int nb_cmd)
{
	t_execve_info	exinfo;

	signal(SIGINT, child_kill_handler);
	if (nb_cmd == 0)
		ft_check_redirect(cmdlst->redirect, data);
	else if (nb_cmd == 1)
	{
		if (ft_check_redirect(cmdlst->redirect, data) == 0)
		{
			data->pack->stdout_fd = ft_get_stdout_fd(cmdlst);
			exinfo = get_exinfo(cmdlst, data, &data->pack->return_code);
			one_command_exec(cmdlst, data, &exinfo);
		}
	}
	else
		ft_pipex(cmdlst, data, fd, nb_cmd);
	return (0);
}

int	exec(t_cmdlst *cmdlst, t_data *data)
{
	int	fd[2][2];
	int	nb_cmd;

	nb_cmd = get_nb_cmd(cmdlst);
	if (pipe(fd[0]) == -1)
	{
		close_all_fd();
		return (1);
	}
	if (pipe(fd[1]) == -1)
	{
		close_all_fd();
		return (1);
	}
	data->pack = ft_initialize_package(nb_cmd);
	if (!data->pack)
		return (1);
	ft_treat_nb_cmd(cmdlst, data, fd, nb_cmd);
	free(data->pack->pid);
	free(data->pack);
	close_all_fd();
	return (0);
}
