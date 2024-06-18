/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:42:16 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 17:38:22 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

# include "./struct.h"

// struct utils
unsigned int	get_nb_arg(t_arg *arg);
unsigned int	get_nb_env(t_env *env);
unsigned int	get_nb_cmd(t_cmdlst *lst);
unsigned int	get_nb_here_doc(t_cmdlst *lst);

// free utils
void			*free_env_struct(t_env *env);
void			*free_char_tab(char **tab);
void			*multi_free_2char_and_ptr(char *str1, char *str2, void *ptr);

// sig utils
void			heredoc_kill_handler(int num);
void			child_kill_handler(int num);
void			reset_signals(void);
void			did_sigkill(int *sig, int *res);

// export utils
void			ft_get_sorted_env(t_env *env);
void			ft_sorted_print(t_env *env, int fd);
int				ft_export_err_print(char *str);
int				is_env_valid(char *env);

#endif