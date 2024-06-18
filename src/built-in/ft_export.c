/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 06:08:33 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 14:03:06 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_val(char *join, char *key, char *val, t_env *env)
{
	char	*new_val;

	new_val = ft_getenv(key, env);
	if (new_val)
		join = ft_strjoin_r(join, new_val, &join);
	if (join)
		join = ft_strjoin_r(join, val, &join);
	return (join);
}

static char	*ft_add_export(char *export_val, t_env *env)
{
	char	*key;
	char	*val;
	char	*join;

	key = ft_strndup(export_val, get_egal_index(export_val) - 1);
	if (!key)
		return (NULL);
	val = get_val(export_val);
	if (!val)
	{
		free(key);
		return (NULL);
	}
	join = ft_strjoin(key, "=");
	if (join && !does_key_exist(key, env))
		join = ft_strjoin_r(join, val, &join);
	else if (join && does_key_exist(key, env))
		join = add_val(join, key, val, env);
	free(key);
	free(val);
	return (join);
}

static int	val_process(char *export_val, t_env **env)
{
	char	*addjoin;

	if (is_env_valid(export_val) == 0)
		return (ft_export_err_print(export_val));
	else if (is_env_valid(export_val) == 1)
	{
		if (ft_putenv(export_val, env) == 1)
			return (1);
	}
	else if (is_env_valid(export_val) == 2)
	{
		addjoin = ft_add_export(export_val, *env);
		if (ft_putenv(addjoin, env) == 1)
			return (1);
		free(addjoin);
	}
	return (0);
}

int	ft_export(t_arg *arg, t_env **env, int fd)
{
	int		return_val;

	return_val = 0;
	if (get_nb_arg(arg) == 1)
		ft_sorted_print(ft_copy_env(*env), fd);
	else
	{
		arg = arg->next;
		while (arg)
		{
			if (val_process(arg->val, env) == 1)
				return_val = 1;
			arg = arg->next;
		}
	}
	return (return_val);
}
