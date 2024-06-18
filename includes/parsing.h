/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:26:58 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 21:12:16 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int			ft_check_in_quotes(char c, int *quotes);
char		*ft_strjoin_r(char const *s1, char const *s2, char **to_free);
t_cmdlst	*ft_parsing(char *cmd, t_data *data);
int			len_str_tab(char **array);
int			arg_remove_one(t_arg **args, int free_val);
int			free_str_tab_n(char **array, int n);
int			strcmp_len(char *s1, char *s2);
int			is_forbidden(char c);
int			contains_only(char *str, char c);
int			env_name_size(char *env);
void		print_args(t_arg *args);
int			get_arg_type(char *str);
int			append_out_args(t_arg **args, char *op, t_outlst **out \
				, t_cmdlst *cmd);
int			strarr_append(char ***array, char *str);
int			index_of_newline(char *str);
int			replace_var(char *var_val, char *n_arg, int *n_cur);
char		*replace_delimiter(char *arg);
int			cmdlst_append_args(t_arg **args, t_cmdlst *new);
void		remove_interogation(char **new_arg, char *arg);
t_cmdlst	*cmdlst_last(t_cmdlst *lst);
t_outlst	*outlst_new(char *filename, int action);
int			replace_in_cmd(char **cmd, int last_exit_val, char **env);
int			cmdlst_clear(t_cmdlst **lst);
int			outlst_append(t_outlst **lst, char *filename, char *special);
int			append_in_args(t_arg **args, char *op, char ***array \
				, t_cmdlst *cmdlst);
void		ft_print_error(char *error, char *near);
t_outlst	*outlst_last(t_outlst *lst);
int			index_of(char *str, char *search, int n);
int			free_str_tab(char **array);
int			ft_iswhitespace(char c);
int			arg_clear(t_arg **arg);
char		*ft_get_env(char *env_str, int last_exit, char **env, \
			int in_quotes);
int			ft_check_quotes(char *cmd);
int			get_env_var_size(char *str);
char		*ft_strldup(const char *s1, int size);
int			handle_space_in_quotes(t_arg **args, char *cmd, int i \
				, int *in_quotes);
int			lst_append(t_arg **args, char *str);
int			free_str(char *str);
int			ft_strcat(char *dst, char *src);
int			replace_hdoc_file(t_cmdlst *tmp, int last_exit_val, char **env);
char		*malloc_new_arg_env(char *arg, int last_exit_val, char **env);
int			is_sep(char *str);
int			redirect_add(t_redirect **redirect, int type, char *name);
int			redirect_clear(t_redirect **redirect);
int			replace(t_cmdlst **cmdlst, int last_exit_val, char **env);
int			ft_check_specials(t_arg *args, t_data *data);
char		*create_new_arg(char *arg);
char		*replace_env_heredoc(char *arg, int last_exit_val, char **env);
void		remove_empty_command(t_cmdlst *tmp);
int			check_pipe_null(t_arg *tmp, t_data *data, int *special);
int			create_cmd_lst(t_cmdlst **cmdlst, t_arg *args);
int			check_str_redirect(char	**str, t_data *data);
char		*process_arg(char *arg, char *new_arg, int last_exit_val \
				, char **env);
int			get_last_index(char *str, int last_i);
int			ft_is_redirect(char c);
int			handle_cmd_logic(t_cmd_info *info);
int			ft_unquote_strtok(t_arg **args, char *cmd);
int			get_last_arg(char *str, int last_quote);
int			check_redirect_file(t_cmdlst *cmdlst, t_data *data);
int			replace_in_quotes(t_arg **args, int last_exit_val, char **env);
int			ft_is_token(char c);
t_redirect	*init_redirect(void);
int			ft_last_unquoted_index(char *str, int *in_quotes);
int			replace_env_heredoc_address(char **arg, int last_exit_val \
					, char **env);
void		re_check_quotes(char *str, int *in_quotes, int i);
int			handle_delimiter_in_quotes(t_arg **args, char *cmd, int i \
					, int *in_quotes);
int			update_last_i(char *cmd, int last_i, int i);
int			append_arg(t_arg **args, char *cmd, int *i, int last_i);
int			ft_check_heredoc(char *buffer, char *delimiter);
char		*ft_parse_buffer(char *str, char *limiter, t_data *data);

#endif