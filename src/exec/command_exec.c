/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:13:04 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 20:17:50 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_built_in(t_cmdlst *cmdlst, t_data *data, t_cmdlst *tmp, \
		t_execve_info *exinfo)
{
	int		return_code;
	bool	exit_val;

	return_code = 0;
	if (ft_strncmp(cmdlst->args->val, "echo", 5) == 0)
		return_code = ft_echo(cmdlst->args, 1);
	else if (ft_strncmp(cmdlst->args->val, "exit", 5) == 0)
		return_code = ft_exit(cmdlst->args, data->return_val, &exit_val, 1);
	else if (ft_strncmp(cmdlst->args->val, "pwd", 4) == 0)
		return_code = ft_pwd(1);
	else if (ft_strncmp(cmdlst->args->val, "env", 4) == 0)
		return_code = ft_env(data->env, 1);
	else if (ft_strncmp(cmdlst->args->val, "cd", 3) == 0)
		return_code = ft_cd(cmdlst->args, data->env);
	else if (ft_strncmp(cmdlst->args->val, "export", 7) == 0)
		return_code = ft_export(cmdlst->args, &(data->env), 1);
	else if (ft_strncmp(cmdlst->args->val, "unset", 6) == 0)
		return_code = ft_unset(cmdlst->args, &(data->env));
	clean_exit(exinfo, data, tmp, return_code);
}

void	no_pipe_built_in(t_cmdlst *cmdlst, t_data *data, \
		t_execve_info *exinfo, int fd)
{
	bool	do_end;

	if (ft_strncmp(cmdlst->args->val, "echo", 5) == 0)
		data->return_val = ft_echo(cmdlst->args, fd);
	else if (ft_strncmp(cmdlst->args->val, "exit", 5) == 0)
	{
		do_end = true;
		data->return_val = ft_exit(cmdlst->args, data->return_val, &do_end, 0);
		if (do_end == true)
		{
			close_all_fd();
			rl_clear_history();
			clean_exit(exinfo, data, cmdlst, data->return_val);
		}
	}
	else if (ft_strncmp(cmdlst->args->val, "pwd", 4) == 0)
		data->return_val = ft_pwd(fd);
	else if (ft_strncmp(cmdlst->args->val, "env", 4) == 0)
		data->return_val = ft_env(data->env, fd);
	else if (ft_strncmp(cmdlst->args->val, "cd", 3) == 0)
		data->return_val = ft_cd(cmdlst->args, data->env);
	else if (ft_strncmp(cmdlst->args->val, "export", 7) == 0)
		data->return_val = ft_export(cmdlst->args, &(data->env), fd);
	else if (ft_strncmp(cmdlst->args->val, "unset", 6) == 0)
		data->return_val = ft_unset(cmdlst->args, &(data->env));
}

int	one_command_exec(t_cmdlst *cmdlst, t_data *data, t_execve_info *exinfo)
{
	if (is_a_built_in(cmdlst->args->val))
		no_pipe_built_in(cmdlst, data, exinfo, data->pack->stdout_fd);
	else if (exinfo->filename)
	{
		data->pack->pid[0] = fork();
		if (data->pack->pid[0] < 0)
			return (1);
		if (data->pack->pid[0] == 0)
		{
			ft_redirect_stdin(cmdlst, data, adjust_hdoc(cmdlst, -1));
			ft_redirect_outfile(cmdlst);
			reset_signals();
			close_all_fd();
			execve(exinfo->filename, exinfo->argtab, exinfo->envtab);
		}
		check_status(data->pack->pid[0], data->pack->status, &data->return_val);
	}
	else
		data->return_val = data->pack->return_code;
	free(exinfo->filename);
	free_char_tab(exinfo->argtab);
	free_char_tab(exinfo->envtab);
	return (0);
}

void	ft_execute_command(t_cmdlst *lst, t_data *data, t_cmdlst *tmp)
{
	t_execve_info	exinfo;

	exinfo = get_exinfo(lst, data, &data->pack->return_code);
	if (ft_check_redirect(lst->redirect, data) == 1)
		clean_exit(&exinfo, data, tmp, 1);
	ft_redirect_stdin(lst, data, data->hdoc_index);
	ft_redirect_outfile(lst);
	close_all_fd();
	if (lst->args && is_a_built_in(lst->args->val))
		pipe_built_in(lst, data, tmp, &exinfo);
	else if (exinfo.filename)
		execve(exinfo.filename, exinfo.argtab, exinfo.envtab);
	else
		clean_exit(&exinfo, data, tmp, data->pack->return_code);
}

int	re_pipe(int pipe_index, int fd[2][2])
{
	close(fd[1 - pipe_index][0]);
	close(fd[pipe_index][1]);
	if (pipe(fd[1 - pipe_index]) == -1)
	{
		close_all_fd();
		return (1);
	}
	return (0);
}
