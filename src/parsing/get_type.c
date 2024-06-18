/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:59:41 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 19:28:00 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_arg_type(char *str)
{
	if (!strcmp_len(str, "|"))
		return (1);
	if (!strcmp_len(str, "&&"))
		return (2);
	if (!strcmp_len(str, "||"))
		return (3);
	if (!strcmp_len(str, ";"))
		return (4);
	return (0);
}

int	is_sep(char *str)
{
	if (get_arg_type(str) != 0)
		return (1);
	if (!strcmp_len(str, ">"))
		return (1);
	if (!strcmp_len(str, "<"))
		return (1);
	if (!strcmp_len(str, "<<"))
		return (1);
	if (!strcmp_len(str, ">>"))
		return (1);
	if (!strcmp_len(str, "&"))
		return (1);
	if (!strcmp_len(str, ";"))
		return (1);
	return (0);
}

int	ft_is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_is_token(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_str_redirect(char	**str, t_data *data)
{
	while (*str)
	{
		if (ft_is_redirect(*str[0]) && ft_strlen(*str) == 1)
		{
			data->return_val = 2;
			return (ft_print_error("syntax error", *str), 1);
		}
		str++;
	}
	return (0);
}
