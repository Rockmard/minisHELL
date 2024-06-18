/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:16:34 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/13 19:33:52 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sig_received = 0;

static void	main_kill_handler(int num)
{
	g_sig_received = num;
	ft_printf("\n");
	replace_prompt();
}

static void	ft_minishell(t_data *data, t_cmdlst *lst)
{
	int	parsing_res;

	while (42 != 69 && 420 != 8)
	{
		data->here_doc_name = NULL;
		signal(SIGINT, main_kill_handler);
		signal(SIGQUIT, SIG_IGN);
		parsing_res = ft_parsing_management(data, &lst, &g_sig_received);
		if (parsing_res == 1)
			continue ;
		else if (parsing_res == 2)
			break ;
		if (ft_here_doc_management(lst, data))
			continue ;
		exec(lst, data);
		clear_here_doc(data);
		cmdlst_clear(&lst);
	}
}

int	main(int ac, char **av, char **e)
{
	t_cmdlst	*lst;
	t_data		data;

	(void)ac;
	(void)av;
	lst = NULL;
	data.return_val = 0;
	data.env = get_t_env(e);
	ft_change_shlvl(data.env);
	ft_minishell(&data, lst);
	did_sigkill(&g_sig_received, &data.return_val);
	free_env_struct(get_top_env(data.env));
	rl_clear_history();
	return (data.return_val);
}
