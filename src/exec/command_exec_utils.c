/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:00:46 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/11 15:37:26 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_a_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	return (0);
}

void	ft_usleep(int millisec)
{
	int	j;

	while (millisec > 0)
	{
		j = 0;
		while (j < 1000000)
			j++;
		millisec--;
	}
}

void	check_status(int pid, int status, int *res)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*res = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		*res = WTERMSIG(status) + 128;
		if (WTERMSIG(status) == 3)
			ft_putstr_fd("Quit (core dumped)\n", 1);
		else if (WTERMSIG(status) == 11)
			ft_putstr_fd("Segmentation fault (core dumped)\n", 1);
		else if (WTERMSIG(status) == 13)
			ft_putstr_fd("Broken pipe\n", 1);
	}
}

void	clean_exit(t_execve_info *exinfo, t_data *data, t_cmdlst *tmp, int res)
{
	free(exinfo->filename);
	if (data->pack->pid)
		free(data->pack->pid);
	free(data->pack);
	free_char_tab(exinfo->argtab);
	free_char_tab(exinfo->envtab);
	free_char_tab(data->here_doc_name);
	free_env_struct(data->env);
	cmdlst_clear(&tmp);
	rl_clear_history();
	close_all_fd();
	exit(res);
}

int	close_all_fd(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		if (close(i) == -1)
			return (1);
		i++;
	}
	return (0);
}
