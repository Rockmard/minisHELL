/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:31:28 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/12 23:42:02 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_in_quotes(char c, int *quotes)
{
	int	in_quotes;

	in_quotes = *quotes;
	if (c == '\'')
	{
		if (in_quotes == 0)
			*quotes = 1;
		else if (in_quotes == 1)
			*quotes = 0;
	}
	if (c == '"')
	{
		if (in_quotes == 0)
			*quotes = 2;
		else if (in_quotes == 2)
			*quotes = 0;
	}
	return (in_quotes);
}

int	ft_check_quotes(char *cmd)
{
	int	in_quotes;
	int	i;

	i = 0;
	in_quotes = 0;
	while (cmd[i])
	{
		ft_check_in_quotes(cmd[i], &in_quotes);
		if (in_quotes == 0 && is_forbidden(cmd[i]) && cmd[i] != ' ')
			return (ft_print_error("syntax error", &cmd[i]), 1);
		i++;
	}
	if (in_quotes == 1)
		ft_print_error("syntax error", "'");
	if (in_quotes == 2)
		ft_print_error("syntax error", "\"");
	return (in_quotes != 0);
}

int	check_last_argument(t_arg *tmp, t_data *data)
{
	if (!tmp->next)
	{
		if (is_sep(tmp->val) && strcmp_len(tmp->val, ";"))
		{
			data->return_val = 2;
			return (ft_print_error("syntax error", tmp->val), 1);
		}
	}
	return (0);
}

int	ft_check_specials(t_arg *args, t_data *data)
{
	t_arg	*tmp;
	int		special;

	tmp = args;
	if (check_pipe_null(tmp, data, &special))
		return (1);
	while (tmp)
	{
		if (is_sep(tmp->val))
		{
			if (special && ft_strncmp(">", tmp->val, 1) == 0 && \
				ft_strncmp("<", tmp->val, 1) == 0)
			{
				data->return_val = 2;
				return (ft_print_error("syntax error", tmp->val), 1);
			}
			special = 1;
		}
		else
			special = 0;
		if (check_last_argument(tmp, data))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	remove_interogation(char **new_arg, char *arg)
{
	char	*i_in_new;
	char	*i_in_arg;
	int		in_quotes;
	int		i;

	in_quotes = 0;
	i = 0;
	i_in_new = ft_strchr(*new_arg, '?');
	i_in_arg = ft_strchr(arg, '?');
	if (!i_in_new || !i_in_arg)
		return ;
	while (arg[i])
	{
		if (ft_check_in_quotes(arg[i], &in_quotes) == in_quotes)
		{
			if (in_quotes == 1 && arg[i] == '?')
				return ;
		}
		if (arg[i + 1] == '?' && arg[i] != '$')
			return ;
		i++;
	}
	ft_memmove(i_in_new, i_in_new + 1, strlen(i_in_new));
}
