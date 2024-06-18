/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:59:52 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 20:07:24 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_here_doc_management(t_cmdlst *lst, t_data *data)
{
	int	hdoc_val;

	if (get_nb_here_doc(lst) > 0)
	{
		hdoc_val = ft_here_doc(lst, data);
		if (hdoc_val != 0)
		{
			clear_here_doc(data);
			cmdlst_clear(&lst);
			if (hdoc_val == 255)
			{
				ft_putendl_fd(\
				"minishell: an error with the here document has occured", 2);
				data->return_val = 1;
			}
			return (1);
		}
	}
	return (0);
}

int	ft_env_management(t_data *data, t_cmdlst *lst)
{
	char	**envp;

	envp = ft_get_envtab(data->env);
	if (!envp)
		return (1);
	replace(&lst, data->return_val, envp);
	free_char_tab(envp);
	ft_change_pwd(data->env);
	return (0);
}

int	ft_parsing_management(t_data *data, t_cmdlst **lst, int *sig)
{
	char		*line;
	t_cmdlst	*tmp;

	line = get_input(data->env);
	if (!line)
		return (2);
	did_sigkill(sig, &data->return_val);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (1);
	}
	tmp = ft_parsing(line, data);
	free(line);
	if (!tmp)
		return (1);
	ft_env_management(data, tmp);
	if (!tmp->cmd)
	{
		cmdlst_clear(&tmp);
		data->return_val = 0;
		return (1);
	}
	*lst = tmp;
	return (0);
}
