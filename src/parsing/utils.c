/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:41:08 by nrontey           #+#    #+#             */
/*   Updated: 2024/05/27 16:09:11 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*ft_argnew(void *content);

void	ft_argadd_back(t_arg **lst, t_arg *new);

int	lst_append(t_arg **args, char *str)
{
	t_arg	*new;

	new = ft_argnew(str);
	if (!new)
		return (arg_clear(&new));
	ft_argadd_back(args, new);
	return (1);
}

int	ft_strcat(char *dst, char *src)
{
	int	cur;

	cur = 0;
	while (src[cur])
	{
		dst[cur] = src[cur];
		cur++;
	}
	return (cur);
}

int	contains_only(char *str, char c)
{
	int	cur;

	cur = -1;
	while (str[++cur])
		if (str[cur] != c)
			return (0);
	return (1);
}

int	env_name_size(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

int	ft_iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r');
}
