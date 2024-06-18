/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:19:16 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/04 14:27:32 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "./minishell.h"

int	ft_echo(t_arg *arg, int fd);
int	ft_env(t_env *env, int fd);
int	ft_cd(t_arg *arg, t_env *env);
int	ft_pwd(int fd);
int	ft_exit(t_arg *arg, int exit_code, bool *exit, int pid);
int	ft_export(t_arg *arg, t_env **env, int fd);
int	ft_unset(t_arg *arg, t_env **env);

#endif