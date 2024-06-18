/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:01:07 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 17:37:02 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// readline addon
void	replace_prompt(void);
char	*get_prompt(t_env *env);
char	*get_input(t_env *env);

// tasks management
int		ft_here_doc_management(t_cmdlst *lst, t_data *data);
int		ft_env_management(t_data *data, t_cmdlst *lst);
int		ft_parsing_management(t_data *data, t_cmdlst **lst, int *sig);

#endif