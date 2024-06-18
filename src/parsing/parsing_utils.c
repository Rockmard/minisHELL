/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 02:28:46 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 18:57:30 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_last_unquoted_index(char *str, int *in_quotes)
{
	int	i;
	int	last_unquoted_index;
	int	inside_quotes;

	i = 0;
	last_unquoted_index = -1;
	inside_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' && *in_quotes == 2)
		{
			if (!inside_quotes)
				last_unquoted_index = i;
			inside_quotes = !inside_quotes;
		}
		else if (str[i] == '\'' && *in_quotes == 1)
		{
			if (!inside_quotes)
				last_unquoted_index = i;
			inside_quotes = !inside_quotes;
		}
		ft_check_in_quotes(str[i], in_quotes);
		i++;
	}
	return (last_unquoted_index);
}

void	re_check_quotes(char *str, int *in_quotes, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (ft_check_in_quotes(str[j], in_quotes) == *in_quotes)
			j++;
		else
			j++;
	}
}

int	handle_delimiter_in_quotes(t_arg **args, char *cmd, int i, int *in_quotes)
{
	int		last_i;
	char	*arg;
	t_arg	*tmp;
	char	*tmp_char;

	if (cmd[i] == ' ' || cmd[i] == '\t')
		return (0);
	last_i = ft_last_unquoted_index(cmd + i, in_quotes);
	arg = ft_strldup(cmd + i, last_i);
	if (!arg)
		return (0);
	tmp = *args;
	while (tmp->next)
		tmp = tmp->next;
	tmp_char = ft_strdup(tmp->val);
	free(tmp->val);
	tmp->val = ft_strjoin(tmp_char, arg);
	free(tmp_char);
	i = ft_strlen(arg);
	free(arg);
	return (i);
}

int	update_last_i(char *cmd, int last_i, int i)
{
	if (ft_is_token(cmd[i]))
		last_i = get_last_index(cmd + i, -1);
	else
		last_i = get_last_index(cmd + i, get_last_arg(cmd + i, 0));
	return (last_i);
}

int	append_arg(t_arg **args, char *cmd, int *i, int last_i)
{
	char	*arg;

	arg = ft_strldup(cmd + *i, last_i);
	if (!arg)
		return (0);
	if (!lst_append(args, arg))
		return (0);
	*i += ft_strlen(arg) - 1;
	return (1);
}
