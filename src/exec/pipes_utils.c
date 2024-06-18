/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:40:30 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/11 13:55:45 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_execve_info	get_exinfo(t_cmdlst *cmdlst, t_data *data, int *res)
{
	t_execve_info	exinfo;

	if (!cmdlst->args)
		exinfo.filename = ft_get_filename(NULL, \
		ft_getenv("PATH", data->env), res);
	else
		exinfo.filename = ft_get_filename(cmdlst->args->val, \
		ft_getenv("PATH", data->env), res);
	exinfo.argtab = ft_get_argtab(cmdlst->args);
	exinfo.envtab = ft_get_envtab(data->env);
	return (exinfo);
}

t_pipes_package	*ft_initialize_package(int nb_cmd)
{
	t_pipes_package	*pack;

	pack = malloc(sizeof(t_pipes_package));
	pack->return_code = 0;
	pack->status = 0;
	pack->stdout_fd = 1;
	if (nb_cmd == 0)
		pack->pid = NULL;
	else
	{
		pack->pid = ft_calloc(sizeof(int), nb_cmd);
		if (!pack->pid)
			return (NULL);
	}
	return (pack);
}

void	ft_pipes_exchange(int i, int nb_cmd, int fd[2][2])
{
	if (i != 0 && (i % 2) == 0)
		dup2(fd[1][0], STDIN_FILENO);
	else if (i != 0)
		dup2(fd[0][0], STDIN_FILENO);
	if (i != nb_cmd - 1)
		dup2(fd[i % 2][1], STDOUT_FILENO);
}

void	ft_end_pipes(int nb_cmd, t_pipes_package *pack, int *res)
{
	int	i;

	close_all_fd();
	i = 0;
	while (i < nb_cmd)
	{
		waitpid(pack->pid[i], &pack->status, 0);
		if (i == nb_cmd - 1)
			check_status(pack->pid[nb_cmd - 1], pack->status, res);
		i++;
	}
}
