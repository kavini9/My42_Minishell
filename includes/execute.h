/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:19:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/28 22:48:48 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef enum e_redirect_type
{
    REDIR_HDOC,
	REDIR_INP,
	REDIR_OUTP,
	REDIR_APPEN,
}   t_redir_type;

typedef struct redir
{
    t_redir_type    type;//ambiguoous redir. If it comes from expansion and has space then it is ambiguous redirection. also if NULL
    char    *fname_o_del;
	int	*exp_flag;
    t_redir *next;
}   t_redir;

typedef struct s_errnote
{
	char *cmd_path;
	char *strerr;
}	t_errnote;


typedef struct s_cmd
{
	char		**cmd;
//  int			cmd_id;
	int			hdoc_st_pos;
//	int			cmd_exit_code;
	t_errnote	err_note;
    t_redir     *redir;
} t_cmd;


void    execin_child(t_msh *msh, t_cmd *cmd, int prev_rd_fd, int i);
void    safe_pipefork_fail(t_msh *msh, int prev_rd_fd, int *pipe_fd , int err_data_pack);
void    set_pipe_chain(int *prev_rd_fd, int *pipe_fd, int cmd_count, int i);
void	run_child_proc(t_msh *msh, t_cmd *cmd, int rd_fd, int wr_fd);
void	wait_child(t_msh *msh, int i, pid_t pid);

void    execute_cmd(t_msh *msh, t_cmd *cmd);
void	get_cmd_path(t_msh *msh, t_cmd *cmd, char *cmd_name, char **cmd_path);
char	*get_path_array(t_msh *msh, char **envl);
int	access_check(t_msh *msh, t_cmd *cmd, char *cmd_path);

void    redirect_io(t_msh *msh, t_cmd *cmd, int fd, int i);
void	redirect_pipe(t_msh *msh, int rd_fd, int wr_fd);
int	open_file(t_msh *msh, t_redir_type type, char *fname);
int	dup_io(t_msh *msh, int oldfd, int newfd);
void	close_all_hdocfd(int *hdocfd_l);

void    here_doc(t_msh *msh, t_cmd **cmd, int *hdocfd_l, int i);
void    get_here_doc(t_msh *msh, t_redir *redir, int *hdoc_fd);

#endif

