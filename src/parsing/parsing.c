/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:23:50 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 21:08:41 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_last_quote(char *str, int last_i);

int	get_last_arg(char *str, int last_quote)
{
	char	**tokens_tab;
	int		last_i;
	int		test_i;
	int		i;

	tokens_tab = ft_split("&& || | << < >> > & ;", ' ');
	if (!tokens_tab)
		return (0);
	last_i = index_of_newline(str + last_quote);
	i = -1;
	while (tokens_tab[++i])
	{
		test_i = index_of(str + last_quote, tokens_tab[i], 1);
		if (test_i < last_i)
		{
			free_str_tab(tokens_tab);
			return (test_i + last_quote);
		}
	}
	free_str_tab(tokens_tab);
	return (last_i + last_quote);
}

static int	get_last_quote(char *str, int last_i)
{
	int		last_index;

	last_index = -2;
	if (str[0] == '\'')
		last_index = get_last_arg(str, index_of(str + 1, "'", 1) + 2);
	else if (last_i > -1 && index_of(str, "'", 1) < last_i)
		last_index = get_last_arg(str, index_of(str, "'", 1) + 2);
	else if (str[0] == '"')
		last_index = get_last_arg(str, index_of(str + 1, "\"", 1) + 2);
	else if (last_i > -1 && index_of(str, "\"", 1) < last_i)
		last_index = get_last_arg(str, index_of(str, "\"", 1) + 1);
	return (last_index);
}

int	get_last_index(char *str, int last_i)
{
	int		i_index;
	char	**tokens_tab;
	int		i;

	if (last_i == 0)
		return (0);
	tokens_tab = ft_split("&& || | << < >> > & ;", ' ');
	if (!tokens_tab)
		return (0);
	i_index = get_last_quote(str, last_i);
	if (i_index == 0)
		return (free_str_tab(tokens_tab));
	if (i_index != -2)
		return (i_index + free_str_tab(tokens_tab));
	i = -1;
	while (tokens_tab[++i])
	{
		if ((last_i > -1 && index_of(str, tokens_tab[i], 1) < last_i))
			return (index_of(str, tokens_tab[i], 1) + free_str_tab(tokens_tab));
		if (index_of(str, tokens_tab[i], 1) == 0)
			return (ft_strlen(tokens_tab[i]) + free_str_tab(tokens_tab));
	}
	return (last_i + free_str_tab(tokens_tab));
}

int	handle_space_in_quotes(t_arg **args, char *cmd, int i, int *in_quotes)
{
	int		last_i;
	char	*arg;
	t_arg	*tmp;
	char	*tmp_char;

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

t_cmdlst	*ft_parsing(char *cmd, t_data *data)
{
	t_arg		*args;
	t_cmdlst	*cmd_lst;

	args = NULL;
	if (ft_check_quotes(cmd))
		return (NULL);
	if (!ft_unquote_strtok(&args, cmd))
		return (NULL);
	if (ft_check_specials(args, data))
	{
		arg_clear(&args);
		return (NULL);
	}
	if (!create_cmd_lst(&cmd_lst, args))
	{
		arg_clear(&args);
		return (NULL);
	}
	if (check_redirect_file(cmd_lst, data))
	{
		cmdlst_clear(&cmd_lst);
		return (NULL);
	}
	return (cmd_lst);
}
