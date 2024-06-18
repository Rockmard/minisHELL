/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:53:31 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 17:04:22 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_change_oldpwd(t_env *env)
{
	t_env	*tmp;
	t_env	*oldpwd;
	t_env	*pwd;

	oldpwd = NULL;
	pwd = NULL;
	tmp = get_top_env(env);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 4) == 0)
			pwd = tmp;
		if (ft_strncmp(tmp->name, "OLDPWD", 7) == 0)
			oldpwd = tmp;
		tmp = tmp->next;
	}
	if (oldpwd)
		free(oldpwd->val);
	if (!pwd && oldpwd)
		oldpwd->val = NULL;
	else if (pwd && oldpwd && pwd->val)
		oldpwd->val = ft_strdup(pwd->val);
}

void	ft_change_pwd(t_env *env)
{
	t_env	*tmp;
	t_env	*pwd;
	char	cwd[PATH_MAX];

	pwd = NULL;
	tmp = get_top_env(env);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 4) == 0)
			pwd = tmp;
		tmp = tmp->next;
	}
	if (pwd)
	{
		if (!getcwd(cwd, PATH_MAX))
		{
			perror("getcwd() error");
			return ;
		}
		free(pwd->val);
		pwd->val = ft_strdup(cwd);
	}
}

int	ft_change_shlvl(t_env *env)
{
	char	*putenv_str;
	char	*shlvl_val;
	char	*new_val;
	int		int_val;

	shlvl_val = ft_getenv("SHLVL", env);
	if (!shlvl_val)
		return (1);
	int_val = ft_atoi(shlvl_val);
	if (int_val == 2147483647)
		int_val = 0;
	else
		int_val++;
	new_val = ft_itoa(int_val);
	if (!new_val)
		return (1);
	putenv_str = ft_strjoin("SHLVL=", new_val);
	free(new_val);
	if (!putenv_str)
		return (1);
	ft_putenv(putenv_str, &env);
	free(putenv_str);
	return (0);
}
