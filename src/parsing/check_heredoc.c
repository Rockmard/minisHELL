/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:53:27 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/10 17:15:19 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	replace_hdoc_file(t_cmdlst *tmp, int last_exit_val, char **env)
{
	int			i;
	t_outlst	*tmp3;

	if (tmp->infiles)
	{
		i = 0;
		while (tmp->infiles[i])
		{
			if (!replace_in_cmd(&(tmp->infiles[i]), last_exit_val, env))
				return (0);
			i++;
		}
	}
	tmp3 = tmp->outfiles;
	if (tmp3)
	{
		while (tmp3)
		{
			if (!replace_in_cmd(&(tmp3->filename), last_exit_val, env))
				return (0);
			tmp3 = tmp3->todo;
		}
	}
	return (1);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	process_character(t_process_character *pc, int i)
{
	if (ft_check_in_quotes(pc->arg[i], &(pc->in_quotes)) == pc->in_quotes)
	{
		if (pc->in_quotes > 0 && pc->found_quote != pc->in_quotes)
			pc->new_arg[(pc->new_i)++] = pc->arg[i];
		else if (pc->in_quotes > 0 && pc->found_quote == pc->in_quotes)
		{
			pc->new_arg[(pc->new_i)++] = pc->arg[i];
			pc->found_quote = 0;
		}
		else if (pc->in_quotes > 0)
			pc->found_quote = pc->in_quotes;
		else if (pc->in_quotes == 0)
			pc->new_arg[(pc->new_i)++] = pc->arg[i];
	}
}

char	*replace_delimiter(char *arg)
{
	t_process_character	pc;
	int					i;

	pc.new_arg = (char *)malloc((strlen(arg) + 1) * sizeof(char));
	if (!pc.new_arg)
		return (NULL);
	pc.arg = arg;
	pc.new_i = 0;
	pc.in_quotes = 0;
	pc.found_quote = 0;
	i = 0;
	while (arg[i])
	{
		process_character(&pc, i);
		i++;
	}
	pc.new_arg[pc.new_i] = '\0';
	return (pc.new_arg);
}

int	ft_check_heredoc(char *buffer, char *delimiter)
{
	char	*new_delimiter;

	if (!buffer || !delimiter)
		return (0);
	new_delimiter = replace_delimiter(delimiter);
	if (!new_delimiter)
		return (0);
	if (ft_strcmp(buffer, new_delimiter) == 0)
	{
		free(new_delimiter);
		free(buffer);
		return (1);
	}
	free(new_delimiter);
	return (0);
}
