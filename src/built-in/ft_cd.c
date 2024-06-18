/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:43:13 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 21:29:19 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_err_print(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(s2, 2);
	return (1);
}

int	ft_cd(t_arg *arg, t_env *env)
{
	if (get_nb_arg(arg) == 1)
	{
		if (!ft_getenv("HOME", env))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		else if (ft_strlen(ft_getenv("HOME", env)) == 0)
			return (0);
		else
		{
			if (chdir(ft_getenv("HOME", env)) == -1)
				return (ft_err_print(ft_getenv("HOME", env), strerror(errno)));
			return (0);
		}
	}
	if (get_nb_arg(arg) > 2)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	if (get_nb_arg(arg) > 2)
		return (1);
	if (ft_strlen(arg->next->val) > 0 && chdir(arg->next->val) == -1)
		return (ft_err_print(arg->next->val, strerror(errno)));
	ft_change_oldpwd(env);
	return (0);
}
