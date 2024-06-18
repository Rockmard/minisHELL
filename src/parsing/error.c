/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:52:30 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 19:27:54 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_error(char *error, char *near)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	if (near)
	{
		ft_putstr_fd(": near '", 2);
		ft_putchar_fd(near[0], 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd("\n", 2);
}

int	check_pipe_null(t_arg *tmp, t_data *data, int *special)
{
	*special = 0;
	if (!tmp)
		return (0);
	if (!strcmp_len(tmp->val, "|"))
	{
		data->return_val = 2;
		return (ft_print_error("syntax error", tmp->val), 1);
	}
	return (0);
}

int	replace_env_heredoc_address(char **arg, int last_exit_val, char **env)
{
	char	*old_val;

	if (*arg)
	{
		old_val = *arg;
		*arg = replace_env_heredoc(*arg, last_exit_val, env);
		free(old_val);
		if (!*arg)
			return (0);
	}
	return (1);
}

static int	check_redirect_heredoc(t_cmdlst *cmdlst, t_data *data)
{
	t_outlst	*outfiles;

	if (cmdlst->outfiles)
	{
		outfiles = cmdlst->outfiles;
		while (outfiles)
		{
			if (ft_is_redirect((outfiles->filename[0])) \
				&& ft_strlen(outfiles->filename) == 1)
			{
				data->return_val = 2;
				return (ft_print_error("syntax error", outfiles->filename), 1);
			}
			outfiles = outfiles->todo;
		}
	}
	return (0);
}

int	check_redirect_file(t_cmdlst *cmdlst, t_data *data)
{
	char		**infiles;
	char		**heredoc;

	if (!cmdlst)
		return (0);
	if (cmdlst->infiles)
	{
		infiles = cmdlst->infiles;
		if (check_str_redirect(infiles, data))
			return (1);
	}
	if (cmdlst->here_docs)
	{
		heredoc = cmdlst->here_docs;
		if (check_str_redirect(heredoc, data))
			return (1);
	}
	if (check_redirect_heredoc(cmdlst, data))
		return (1);
	return (0);
}
