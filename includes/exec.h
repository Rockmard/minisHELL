/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:19:36 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/11 13:17:05 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// command exec utils
void			ft_usleep(int millisec);
void			check_status(int pid, int status, int *res);
void			clean_exit(t_execve_info *exinfo, t_data *data, \
				t_cmdlst *tmp, int res);
int				close_all_fd(void);
int				is_a_built_in(char *cmd);

// filename utils
void			ft_print_err_file(char *msg, char *file);
char			*ft_strddup(char *str, int i, int j);
char			*ft_get_full_path(char *folder, char *file);

// execve build
char			*ft_get_filename(char *file, char *path, int *res);
char			**ft_get_envtab(t_env *env);
char			**ft_get_argtab(t_arg *arg);

// exec
int				exec(t_cmdlst *cmdlst, t_data *data);
int				one_command_exec(t_cmdlst *cmdlst, t_data *data, \
				t_execve_info *exinfo);
int				re_pipe(int pipe_index, int fd[2][2]);
void			ft_execute_command(t_cmdlst *lst, t_data *data, t_cmdlst *tmp);
void			pipe_built_in(t_cmdlst *cmdlst, t_data *data, t_cmdlst *tmp, \
				t_execve_info *exinfo);
void			no_pipe_built_in(t_cmdlst *cmdlst, t_data *data, \
				t_execve_info *exinfo, int fd);

// pipes utils
t_execve_info	get_exinfo(t_cmdlst *cmdlst, t_data *data, int *res);
t_pipes_package	*ft_initialize_package(int nb_cmd);
void			ft_end_pipes(int nb_cmd, t_pipes_package *pack, int *res);
void			ft_pipes_exchange(int i, int nb_cmd, int fd[2][2]);
#endif