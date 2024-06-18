/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:32:02 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/04 14:25:08 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) < 2)
		return (false);
	if (str[i++] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(t_arg *arg, int fd)
{
	bool	flag;

	arg = arg->next;
	flag = false;
	while (arg && is_flag(arg->val))
	{
		if (!is_flag(arg->val))
			break ;
		flag = is_flag(arg->val);
		arg = arg->next;
	}
	while (arg)
	{
		ft_putstr_fd(arg->val, fd);
		arg = arg->next;
		if (!arg)
			break ;
		ft_putstr_fd(" ", fd);
	}
	if (!flag)
		ft_putstr_fd("\n", fd);
	return (0);
}
