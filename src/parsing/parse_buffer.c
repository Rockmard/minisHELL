/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 00:04:14 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/11 13:31:14 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	rm_interogation_heredoc(char **new_arg, char *arg)
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
	ft_memmove(i_in_new, i_in_new + 1, strlen(i_in_new));
}

static int	heredoc_arg_len(char *arg, int last_exit_val, char **env)
{
	int		i;
	int		new_len;
	char	*env_val;

	i = 0;
	new_len = 0;
	while (arg[i])
	{
		if (arg[i] == '$' )
		{
			env_val = ft_get_env(arg + i, last_exit_val, env, 0);
			if (!env_val)
				return (-1);
			new_len += ft_strlen(env_val) - 1;
			i += get_env_var_size(arg + i) - 1;
			free(env_val);
		}
		i++;
		new_len++;
	}
	(void)last_exit_val;
	return (new_len);
}

static char	*malloc_new_env_heredoc(char *arg, int last_exit_val, char **env)
{
	char	*new_arg;
	int		new_len;

	new_len = heredoc_arg_len(arg, last_exit_val, env);
	if (new_len == -1)
		return (NULL);
	new_arg = ft_calloc(new_len + 1, sizeof(char));
	if (!new_arg)
		return (NULL);
	return (new_arg);
}

char	*replace_env_heredoc(char *arg, int last_exit_val, char **env)
{
	char	*new_arg;
	int		i;
	int		new_i;
	char	*env_val;

	new_arg = malloc_new_env_heredoc(arg, last_exit_val, env);
	i = -1;
	new_i = 0;
	while (arg[++i] && new_arg)
	{
		if (arg[i] == '$')
		{
			env_val = ft_get_env(arg + i, last_exit_val, env, 0);
			ft_strlcpy(new_arg + new_i, env_val, ft_strlen(env_val) + 1);
			new_i += ft_strlen(env_val);
			i += get_env_var_size(arg + i) - 1;
			free(env_val);
		}
		else
			new_arg[new_i++] = arg[i];
	}
	rm_interogation_heredoc(&new_arg, arg);
	return (new_arg);
}

char	*ft_parse_buffer(char *str, char *limiter, t_data *data)
{
	char	**tab;
	char	*tmp;

	if (!str)
		return (NULL);
	tab = ft_get_envtab(data->env);
	tmp = NULL;
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '\"'))
	{
		tmp = ft_strdup(str);
	}
	else
	{
		tmp = replace_env_heredoc(str, data->return_val, tab);
	}
	free_char_tab(tab);
	return (tmp);
}
