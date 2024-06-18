/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:08:27 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 17:35:18 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_kill_handler(int num)
{
	(void)num;
	ft_printf("\n");
}

void	heredoc_kill_handler(int num)
{
	(void)num;
	ft_printf("\n");
	close(0);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	did_sigkill(int *sig, int *res)
{
	if (*sig == 2)
	{
		*res = 130;
		*sig = 1;
	}
}
