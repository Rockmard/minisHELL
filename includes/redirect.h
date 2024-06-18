/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:31:38 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/10 16:48:03 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

// here_doc
void	clear_here_doc(t_data *data);
char	*ft_get_randoname(char *base_name);
int		buff_error(int fd, int fd_hdoc, t_data *data, char *delimiter);
int		ft_create_here_doc_name(t_cmdlst *lst, t_data *data);
int		ft_here_doc(t_cmdlst *cmdlst, t_data *data);

// stdin redirect utils
int		check_infile(char *name);
int		adjust_hdoc(t_cmdlst *lst, int index);
int		ft_redirect_here_doc(t_cmdlst *lst, t_data *data, int hdoc_index);
int		ft_redirect_infile(t_cmdlst *lst);
int		ft_redirect_stdin(t_cmdlst *lst, t_data *data, int i);

// stdout redirect utils
int		check_outfile(char *name, int type);
int		ft_redirect_outfile(t_cmdlst *lst);
int		ft_get_stdout_fd(t_cmdlst *lst);

int		ft_check_redirect(t_redirect *redirect, t_data *data);

#endif