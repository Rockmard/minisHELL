/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:22:59 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 19:34:42 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_str_tab(char **array)
{
	int	cur;

	cur = 0;
	if (array)
		while (array[cur])
			cur++;
	return (cur);
}

int	strcmp_len(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

int	get_new_arg_len(char *arg, int last_exit_val, char **env)
{
	int		i;
	int		in_quotes;
	int		new_len;
	char	*env_val;

	i = 0;
	in_quotes = 0;
	new_len = 0;
	while (arg[i])
	{
		if (ft_check_in_quotes(arg[i], &in_quotes) == in_quotes)
			new_len++;
		if (in_quotes != 1 && arg[i] == '$' )
		{
			env_val = ft_get_env(arg + i, last_exit_val, env, in_quotes);
			if (!env_val)
				return (-1);
			new_len += ft_strlen(env_val) - 1;
			i += get_env_var_size(arg + i) - 1;
			free(env_val);
		}
		i++;
	}
	(void)last_exit_val;
	return (new_len);
}

int	replace_var(char *var_val, char *n_arg, int *n_cur)
{
	n_arg[(*n_cur) - 1] = 0;
	if (!var_val)
		return (free_str(n_arg));
	*n_cur += ft_strcat(n_arg + (*n_cur) - 1, var_val) - 1;
	return (1);
}

char	*process_arg(char *arg, char *new_arg, int last_exit_val, char **env)
{
	int		i;
	int		in_quotes;
	int		new_i;
	char	*env_val;

	i = -1;
	new_i = 0;
	in_quotes = 0;
	while (arg[++i] && new_arg)
	{
		if (ft_check_in_quotes(arg[i], &in_quotes) == in_quotes)
			new_arg[new_i++] = arg[i];
		if (in_quotes != 1 && arg[i] == '$')
		{
			env_val = ft_get_env(arg + i, last_exit_val, env, in_quotes);
			if (!replace_var(env_val, new_arg, &new_i))
				return (NULL);
			free(env_val);
			i += get_env_var_size(arg + i) - 1;
		}
	}
	return (new_arg);
}
