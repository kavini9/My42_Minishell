/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 16:49:32 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*-------------------------Definitions------------------------*/
# define HEREDOC_MAX 16
# define PID_MAX_LEN 8
# define X_KO 126
# define F_KO 127
# define IS_DIRECTORY "Is a directory"
# define CMD_NOT_FOUND "command not found"

/*-------------------------Includes------------------------*/
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <signal.h>
# include <sys/wait.h>
# include "../lib/libft/libft.h"
# include "define.h"

/*-------------------------Global------------------------*/
extern volatile __sig_atomic_t	g_sig;

/*-------------------------Structs------------------------*/

typedef enum e_do_err
{
	ERRNO	= 0b00001,
	EXTRARG	= 0b00010,
	LOG		= 0b00100,
	CLEAN	= 0b01000,
	EXIT	= 0b10000
}	t_do_err;

typedef enum e_vtype
{
	REG,
	ARR,
	TOK,
	RED,
}	t_vtype;

typedef enum e_redirect_type
{
	REDIR_NONE,
	REDIR_HDOC,
	REDIR_INP,
	REDIR_OUTP,
	REDIR_APPEN,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*fname_o_del;
	int				ambi_o_hdexp;
}	t_redir;

typedef struct s_errnote
{
	char	*cmd_path;
	char	*strerr;
}	t_errnote;

typedef struct s_cmd
{
	char		**cmd;
	int			hdoc_st_pos;
	t_errnote	err_note;
	t_redir		**redir;
}	t_cmd;

typedef struct s_expan
{
	char	*tok;
	char	*suffix;
	char	*prefix;
	char	*exp;
	char	*key;
	char	**tmp_arr;
	int		scan_offset;
}	t_expan;

typedef struct s_token
{
	char			*token;
	char			**expn;
	int				expn_len;
	t_redir_type	redir;
}	t_token;

typedef struct s_parse
{
	char		*line;
	char		**seg;
	t_token		**token;
}	t_parse;

typedef struct s_msh
{
	char	*cwd;
	char	*old_wd;
	char	**envl;
	t_parse	*aux;
	t_cmd	**cmd;
	int		cmd_count;
	int		hdocfd_l[HEREDOC_MAX];
	int		*std_fd;
	int		exit_code;
}	t_msh;

/*-------------------------Main------------------------*/
void	msh_init(t_msh *msh, char **envp);
void	msh_loop(t_msh *msh);
void	msh_parse(t_msh *msh, char *line);
void	msh_execute(t_msh *msh);
int		msh_exit(t_msh *msh, char *line);

/*-------------------------Validation------------------------*/
int		msh_validate_line(t_msh *msh, char **line);
int		validate_pipe(t_msh *msh, char *line);
int		check_redirects(t_msh *msh, char *line);
int		validate_redirect(t_msh *msh, char *line, int *i, char *type);
int		skip_whitespace(char *str, int i);
int		is_input_empty(const char *input);
int		ft_isspace(char c);
int		check_quote(char *line, int limit);
int		check_quotes(char *start, char *end);

/*-------------------------Realloc------------------------*/
void	*msh_realloc(void *ptr, size_t len_prev, size_t len_new, t_vtype type);
void	*free_vtype(void *ptr, t_vtype type);

/*-------------------------Parsing------------------------*/
void	init_parse_structs(t_msh *msh, char *line);
int		count_pipes(char *line);
void	line_split_bypipe(t_msh *msh, char *line, char *start, char **seg_arr);

/*-------------------------Tokenization------------------------*/
void	seg_tokenize(t_msh *msh, t_parse *aux);
void	extract_token(t_msh *msh, t_token **token, char *seg);
int		get_token_len(char *seg, t_token *token, int tok_len, int is_white);
int		set_redir_type(t_token *token, char *seg);

/*-------------------------Parse_utils------------------------*/
int		check_quotes(char *start, char *end);
char	*skip_whitespaces(char **str);
int		redir_skip(char *seg);
char	*remove_quotes(char *q_arg);
int		is_ambi_redir(char **expan, t_cmd *cmd, int len);

/*-------------------------Expansion------------------------*/
void	expand_tokens(t_msh *msh, t_token **token);
void	expscan_token(t_msh *msh, t_token *token, t_expan exp);
void	expand_parameter(t_msh *msh, t_token *token, t_expan *exp);
char	*extract_env_key(char **token);

/*-------------------------Variable Extract------------------------*/
char	*extract_exp_value(t_msh *msh, char *key);
char	*get_process_pid(char *buf, int fd);

/*-------------------------Expansion Array Utils------------------------*/
char	**get_tmp_arr(t_expan *exp, char *exp_dup, int quote_or_redir);
void	adjust_exp_edge(t_msh *msh, t_expan *exp, char *exp_val, int q_context);
void	extend_exp_edge(t_msh *msh, t_expan *exp, int index, int *len);
void	concat_exp_edge(t_msh *msh, t_expan *exp, int spc, int index);
size_t	ft_arrlen(void **arr);

/*-------------------------Expansion Struct Manager------------------------*/
void	init_exp(t_msh *msh, t_token token, t_expan *exp);
void	revise_exp_arr(t_msh *msh, t_token *token, t_expan *exp);

/*-------------------------Command Setup------------------------*/
void	init_cmd_struct(t_msh *msh, int cmd_count);
void	addto_redir_arr(t_msh *msh, t_token *token, t_cmd *cmd, int *len);
void	q_unwrap_append(t_msh *msh, t_cmd *cmd, char *q_arg);
void	addto_cmd_arr(t_msh *msh, t_token *token, t_cmd *cmd);
void	setup_cmd(t_msh *msh, t_token **token, t_cmd **cmd);

/*-------------------------Cleaning / Freeing------------------------*/
void	msh_clean(t_msh *msh);
void	clean_aux(t_msh *msh, t_parse *aux);
void	clean_exp(t_expan *exp);
void	parse_error(t_msh *msh, t_parse *aux, t_expan *exp, char *func_name);
void	free_token(t_token *tok);
void	free_arr(void **arr);
void	free_cmd(t_cmd **cmd);
void	free_redir(t_redir **redir);
void	*free_and_null(void *ptr);

/*-------------------------Reset State------------------------*/
void	reset_cmd_attr(t_msh *msh);

/*-------------------------Errors------------------------*/
void	msh_error(t_msh *msh, t_do_err opt_exc, char *err_msg, char *param);
void	error_log(char *err_msg, char *param, int err_no, int extrarg);

/*-------------------------Builtins------------------------*/

void	builtin_cd(t_msh *msh, char **cmd);
void	cd_path(t_msh *msh, char *path);
void	cd_tilde(t_msh *msh, char *tilde_path);
void	cd_env_var(t_msh *msh, char *dir);
void	msh_wd_update(t_msh *msh);
void	handle_unlinked_cwd(t_msh *msh, char *path);

/*-------------------------Echo------------------------*/
void	builtin_echo(t_msh *msh, char **cmd);

/*-------------------------Env------------------------*/
void	builtin_env(t_msh *msh);

/*-------------------------Exit------------------------*/
void	builtin_exit(t_msh *msh, char **cmd);
int		is_numeric(char *str);

/*-------------------------Export------------------------*/
void	builtin_export(t_msh *msh, char **cmd);
int		is_valid_id(char *x_var);

/*-------------------------Pwd------------------------*/
void	builtin_pwd(t_msh *msh);

/*-------------------------Unset------------------------*/
void	builtin_unset(t_msh *msh, char **cmd);
void	unset_env(char **envl, char *key);

/*-------------------------Execution------------------------*/
void	execin_shell(t_msh *msh, t_cmd *cmd);
int		exec_builtin(t_msh *msh, char **cmd);
int		is_builtin(char **cmd);
void	restore_stdfd(t_msh *msh, int *fd_0, int *fd_1);

void	execin_child(t_msh *msh, t_cmd **cmd, int prev_rd_fd, int i);
void	safe_pipefork_fail(t_msh *msh, int prev_rd_fd, int *pipe_fd,
			int err_data_pack);
void	set_pipe_chain(int *prev_rd_fd, int *pipe_fd, int cmd_count, int i);
void	run_child_proc(t_msh *msh, t_cmd *cmd, int rd_fd, int *pipe);
void	wait_child(t_msh *msh, int i, pid_t pid);

void	execute_cmd(t_msh *msh, t_cmd *cmd, char *cmd_path);
void	get_cmd_path(t_msh *msh, t_cmd *cmd, char *cmd_name, char **cmd_path);
char	**get_path_array(t_msh *msh, char **envl);
int		access_check(t_msh *msh, t_cmd *cmd, char *cmd_path);

/*-------------------------Redirections------------------------*/
void	redirect_io(t_msh *msh, t_cmd *cmd, int fd, int i);
void	redirect_pipe(t_msh *msh, int rd_fd, int wr_fd);
int		open_file(t_redir_type type, char *fname);
int		dup_io(int oldfd, int newfd);
void	close_all_hdocfd(int *hdocfd_l);

void	here_doc(t_msh *msh, t_cmd **cmd, int *hdocfd_l, int i);
void	get_here_doc(t_msh *msh, t_redir *redir, int *hdoc_fd);

/*-------------------------Environment------------------------*/
void	duplicate_env(t_msh *msh, char **envp);
void	generate_mini_env(t_msh *msh);
void	set_shlvl(t_msh *msh, char **envl);

char	*get_env(char **envl, char *var);
void	update_env(t_msh *msh, char *key, char *value);
void	set_env(t_msh *msh, char **envl, char *entry);
void	add_env_var(t_msh *msh, char **envl, char *entry);
void	overwrite_env_var(t_msh *msh, char **env_var, char *entry);

/*-------------------------Signal Handling------------------------*/
void	sigint_handler(int sig);
void	sig_handler_child(int sig);
void	sig_handler_heredoc(int signum);
void	init_sig(void);
void	sig_handler_changer(void);
void	sig_reseted(void);
void	sig_heredoc(void);

#endif