/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:06:27 by tpipi             #+#    #+#             */
/*   Updated: 2024/06/13 21:15:06 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_arg
{
	char			*val;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_outlst
{
	char			*filename;
	int				action;
	struct s_outlst	*todo;
}	t_outlst;

typedef struct s_redirect
{
	int					type;
	char				*name;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmdlst
{
	char				*cmd;
	t_arg				*args;
	char				**infiles;
	t_outlst			*outfiles;
	char				**here_docs;
	int					todo;
	int					stdin_last;
	struct s_redirect	*redirect;
	struct s_cmdlst		*next;
}	t_cmdlst;

typedef struct s_process_character
{
	char	*arg;
	char	*new_arg;
	int		new_i;
	int		in_quotes;
	int		found_quote;
}	t_process_character;

typedef struct s_execve_info
{
	char	*filename;
	char	**argtab;
	char	**envtab;
}	t_execve_info;

typedef struct s_pipes_package
{
	int	*pid;
	int	return_code;
	int	status;
	int	stdout_fd;
}	t_pipes_package;

typedef struct s_here_doc_info
{
	int		fd_stdin;
	int		fd_hdoc;
	char	*delimiter;
	char	*path;
}	t_hdoc_info;

typedef struct s_data
{
	int				return_val;
	int				hdoc_index;
	char			**here_doc_name;
	t_env			*env;
	t_pipes_package	*pack;
}	t_data;

typedef struct s_cmd_info
{
	t_arg	**args;
	char	*cmd;
	int		*i;
	int		*in_quotes;
	int		*last_i;
}	t_cmd_info;

#endif