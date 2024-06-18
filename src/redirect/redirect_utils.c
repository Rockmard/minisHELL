/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:38:57 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/10 16:47:50 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_redirect(t_redirect *redirect, t_data *data)
{
	t_redirect	*tmp;
	int			error;

	tmp = redirect;
	while (tmp)
	{
		if (tmp->type == 0)
			error = check_infile(tmp->name);
		else
			error = check_outfile(tmp->name, tmp->type);
		if (error)
		{
			data->return_val = 1;
			return (error);
		}
		tmp = tmp->next;
	}
	return (0);
}
