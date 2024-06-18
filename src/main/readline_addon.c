/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_addon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:52:35 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 17:34:54 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_prompt(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*get_prompt(t_env *env)
{
	char	*user_name;
	char	*cwd;
	char	*prompt;
	char	*home;

	user_name = ft_getenv("USER", env);
	if (!user_name)
		user_name = "unknown";
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("unknown");
	home = ft_getenv("HOME", env);
	if (!home)
		home = "/";
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		cwd = ft_strjoin_r("~", cwd + ft_strlen(home), &cwd);
	prompt = ft_strjoin(user_name, "@");
	prompt = ft_strjoin_r(prompt, "Minishell", &prompt);
	prompt = ft_strjoin_r(prompt, ":", &prompt);
	prompt = ft_strjoin_r(prompt, cwd, &prompt);
	prompt = ft_strjoin_r(prompt, "$ ", &prompt);
	free(cwd);
	return (prompt);
}

char	*get_input(t_env *env)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt(env);
	input = readline(prompt);
	free(prompt);
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		return (NULL);
	}
	if (ft_strlen(input) == 0)
		return (input);
	add_history(input);
	return (input);
}
