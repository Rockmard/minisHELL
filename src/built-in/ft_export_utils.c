/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:29:20 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/04 14:41:08 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_sorted_env(t_env *env)
{
	char	*tmpname;
	char	*tmpval;
	t_env	*tmp;

	env = get_top_env(env);
	while (env && env->next)
	{
		tmp = env->next;
		while (tmp)
		{
			if (ft_strncmp(env->name, tmp->name, ft_strlen(env->name)) > 0)
			{
				tmpname = env->name;
				tmpval = env->val;
				env->name = tmp->name;
				env->val = tmp->val;
				tmp->name = tmpname;
				tmp->val = tmpval;
			}
			tmp = tmp->next;
		}
		env = env->next;
	}
}

void	ft_sorted_print(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = get_top_env(env);
	ft_get_sorted_env(tmp);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "_", 2) != 0)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->name, fd);
			if (tmp->val)
			{
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(tmp->val, fd);
				ft_putstr_fd("\"", fd);
			}
			ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
	}
	free_env_struct(env);
}

int	ft_export_err_print(char *str)
{
	if (str)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	is_env_valid(char *env)
{
	int	i;

	if (!env || !env[0] || !(ft_isalpha(env[0]) || env[0] == '_'))
		return (0);
	if (env[0] == '_' && env[1] && env[1] == '=')
		return (-1);
	if (env[0] == '_' && env[1] && env[1] == '+' && env[2] && env[2] == '=')
		return (-1);
	i = 1;
	while (env[i] && env[i] != '=')
	{
		if (env[i] == '+' && env[i + 1] && env[i + 1] == '=')
			return (2);
		if (!ft_isalnum(env[i]) && env[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
