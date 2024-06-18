/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:18:41 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/11 15:55:13 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_new_arg_len(char *arg, int last_exit_val, char **env);

int	dollar_lone_quotes(char *arg, int i, int in_quotes)
{
	while (arg[i] != '\0' && arg[i + 1] != '\0')
	{
		if (in_quotes == 2 && arg[i] == '$' && (ft_iswhitespace(arg[i + 1]) || \
			!arg[i + 1] || arg[i + 1] == '\"'))
			return (1);
		if (ft_check_in_quotes(arg[i], &in_quotes) == in_quotes)
			i++;
		i++;
	}
	return (0);
}

char	*special_env(char *env_str, int last_exit, int in_quotes)
{
	char	*quoted_env_str;

	quoted_env_str = NULL;
	if (!ft_strncmp(env_str, "$?", 2))
		return (ft_itoa(last_exit));
	else if (contains_only(env_str, '$'))
		return (ft_strdup(env_str));
	else if (dollar_lone_quotes(env_str, 0, in_quotes))
		return (ft_strdup("$"));
	else if (env_str[1] == '$')
		return (ft_strdup("$"));
	else if (env_str[1] == '\'' || env_str[1] == '"')
	{
		quoted_env_str = ft_strtrim(env_str + 2, "\"'");
		env_str = quoted_env_str;
	}
	else if (!ft_isalpha(env_str[1]) && env_str[1] != '_')
	{
		free(quoted_env_str);
		return (ft_strdup(""));
	}
	free(quoted_env_str);
	return (NULL);
}

char	*ft_get_env(char *env_str, int last_exit, char **env, int in_quotes)
{
	char	*env_val;
	int		env_i;
	int		env_name_len;

	env_val = special_env(env_str, last_exit, in_quotes);
	if (!env_val)
	{
		env_i = 0;
		while (env[env_i])
		{
			env_name_len = env_name_size(env[env_i]);
			if (!ft_strncmp(env[env_i], env_str + 1, env_name_len) && \
				(env_str[env_name_len + 1] == '\0' || \
					!ft_isalnum(env_str[env_name_len + 1])))
				return (ft_strdup(strchr(env[env_i], '=') + 1));
			env_i++;
		}
		return (ft_strdup(""));
	}
	return (env_val);
}

int	get_env_var_size(char *str)
{
	int	i;
	int	num_start;

	if (contains_only(str, '$'))
		return (ft_strlen(str));
	if (!strcmp_len(str, "$?"))
		return (2);
	num_start = 0;
	if (ft_isdigit(str[1]))
		num_start = 1;
	i = 0;
	while (str[i] || (i == 0 && str[i] == '$'))
	{
		if (num_start && (ft_isalpha(str[i]) || str[i] == '_'))
			return (i);
		if (!ft_isalnum(str[i]) && str[i] != '_' && i != 0)
			return (i);
		i++;
	}
	return (i);
}

char	*malloc_new_arg_env(char *arg, int last_exit_val, char **env)
{
	char	*new_arg;
	int		new_len;

	new_len = get_new_arg_len(arg, last_exit_val, env);
	if (new_len == -1)
		return (NULL);
	new_arg = ft_calloc(new_len + 1, sizeof(char));
	if (!new_arg)
		return (NULL);
	return (new_arg);
}
