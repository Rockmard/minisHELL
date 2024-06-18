/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:40:30 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 20:07:51 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_in_arg(char *arg, int last_exit_val, char **env)
{
	char	*new_arg;

	new_arg = malloc_new_arg_env(arg, last_exit_val, env);
	if (ft_strncmp("\"\"", arg, 3) == 0 || ft_strncmp("\'\'", arg, 3) == 0)
	{
		free(new_arg);
		return (ft_strdup("\b"));
	}
	new_arg = process_arg(arg, new_arg, last_exit_val, env);
	remove_interogation(&new_arg, arg);
	return (new_arg);
}

int	replace_in_cmd(char **cmd, int last_exit_val, char **env)
{
	char	*old_val;

	if (*cmd)
	{
		old_val = *cmd;
		*cmd = replace_in_arg(*cmd, last_exit_val, env);
		free(old_val);
		if (!*cmd)
			return (0);
	}
	return (1);
}

int	replace_in_quotes(t_arg **args, int last_exit_val, char **env)
{
	t_arg	*tmp;
	char	*old_val;

	tmp = *args;
	while (tmp)
	{
		if (tmp->val)
		{
			old_val = tmp->val;
			tmp->val = replace_in_arg(tmp->val, last_exit_val, env);
			free(old_val);
			if (!tmp->val)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static void	remove_empty(t_cmdlst *tmp, t_arg *tmp2)
{
	remove_empty_command(tmp);
	tmp2 = tmp->args;
	while (tmp2 && tmp2->next)
	{
		if (ft_strlen(tmp2->next->val) == 0)
			arg_remove_one(&tmp2->next, 2);
		else if (ft_strncmp("\b", tmp2->next->val, 1) == 0)
		{
			free(tmp2->next->val);
			tmp2->next->val = ft_strdup("");
		}
		tmp2 = tmp2->next;
	}
}

int	replace(t_cmdlst **cmdlst, int last_exit_val, char **env)
{
	t_cmdlst	*tmp;
	t_arg		*tmp2;
	t_redirect	*tmp3;

	tmp = *cmdlst;
	tmp2 = NULL;
	while (tmp)
	{
		if (!replace_in_quotes(&(tmp->args), last_exit_val, env))
			return (0);
		if (!replace_env_heredoc_address(&(tmp->cmd), last_exit_val, env))
			return (0);
		if (!replace_hdoc_file(tmp, last_exit_val, env))
			return (0);
		tmp3 = tmp->redirect;
		while (tmp3)
		{
			if (!replace_in_cmd(&(tmp3->name), last_exit_val, env))
				return (0);
			tmp3 = tmp3->next;
		}
		remove_empty(tmp, tmp2);
		tmp = tmp->next;
	}
	return (1);
}
