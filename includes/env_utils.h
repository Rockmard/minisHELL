/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:09:14 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 17:05:03 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include <stdlib.h>
# include <stdbool.h>

# include "./struct.h"
# include "./utils.h"
# include "../src/libft/libft.h"

// env_utils folder
int		get_egal_index(char *str);
int		does_key_exist(char *key, t_env *env);
char	*get_val(char *str);
char	*ft_strndup(char *str, int i);
t_env	*get_t_env(char **env);
t_env	*ft_copy_env(t_env *env);
t_env	*add_env(char *name, char *val, t_env *env);
t_env	*get_top_env(t_env *env);
t_env	*get_bot_env(t_env *env);

// env update
void	ft_change_pwd(t_env *env);
void	ft_change_oldpwd(t_env *env);
int		ft_change_shlvl(t_env *env);

// main functions
int		ft_putenv(char *str, t_env **env);
char	*ft_getenv(char *key, t_env *env);

#endif