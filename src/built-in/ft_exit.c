/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:11:42 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 02:36:01 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ll_overflow(long long int nb, const char c)
{
	return (nb > (nb * 10 + c - '0'));
}

static bool	ft_add_number(char c, int *i, long long int *nb)
{
	if (!((c >= '0' && c <= '9') || c == ' ' || c == 9) || ll_overflow(*nb, c))
		return (false);
	if (c >= '0' && c <= '9')
		(*nb) = (*nb) * 10 + c - '0';
	(*i)++;
	return (true);
}

static bool	ft_atoll(const char *str, long long int *nb)
{
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] && ft_strncmp("-9223372036854775808", str + i, 21) == 0)
		return (true);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_add_number(str[i], &i, nb))
			return (false);
	}
	(*nb) = sign * (*nb);
	return (true);
}

int	ft_exit(t_arg *arg, int exit_code, bool *exit, int pid)
{
	long long int	return_val;

	return_val = 0;
	arg = arg->next;
	if (pid == 0)
		ft_printf("exit\n");
	if (!arg)
		return (exit_code);
	else if (ft_atoll(arg->val, &return_val) == false)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg->val, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	else if (get_nb_arg(arg) > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		*exit = false;
		return (1);
	}
	return (return_val % 256);
}
