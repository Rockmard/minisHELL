/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_strtok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:09:02 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 21:09:27 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_cmd_logic(t_cmd_info *info)
{
	re_check_quotes(info->cmd, info->in_quotes, *(info->i));
	if ((info->cmd[*(info->i)] == ' ' || info->cmd[*(info->i)] == '\t') \
			&& *(info->in_quotes) == 0)
		return (0);
	else if ((info->cmd[*(info->i)] == ' ' || info->cmd[*(info->i)] == '\t') \
			&& *(info->in_quotes) > 0)
	{
		*(info->i) += handle_space_in_quotes(info->args, info->cmd \
				, *(info->i), info->in_quotes);
		return (0);
	}
	else if (ft_is_token(info->cmd[*(info->i)]) && *(info->in_quotes) > 0)
	{
		*(info->i) += handle_delimiter_in_quotes(info->args, info->cmd \
				, *(info->i), info->in_quotes);
		return (0);
	}
	*(info->last_i) = update_last_i(info->cmd, *(info->last_i), *(info->i));
	if (!*(info->last_i))
		return (arg_clear(info->args));
	if (!append_arg(info->args, info->cmd, info->i, *(info->last_i)))
		return (arg_clear(info->args));
	return (1);
}

int	ft_unquote_strtok(t_arg **args, char *cmd)
{
	int			i;
	int			last_i;
	int			in_quotes;
	t_cmd_info	info;

	i = -1;
	in_quotes = 0;
	info.args = args;
	info.cmd = cmd;
	info.i = &i;
	info.in_quotes = &in_quotes;
	info.last_i = &last_i;
	while (i < (int)ft_strlen(cmd) && cmd[++i])
	{
		if (!handle_cmd_logic(&info))
			continue ;
	}
	return (1);
}
