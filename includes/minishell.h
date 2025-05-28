/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/28 17:39:33 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define  HEREDOC_MAX 16

# define X_KO 126
# define F_KO 127
#define IS_DIRECTORY "Is a directory" 
# define CMD_NOT_FOUND "command not found"

# include <readline/readline.h> //for readline
# include <readline/history.h> //for readline add_history function
# include <stdio.h> //temporary printf in msh_clean. delete later if you use your own
# include <stdlib.h> //for exit
# include <stdint.h> //for uint8_t in exit
# include <string.h> //for strerror(errnum)
# include <errno.h> //for using errno in strerror
# include <unistd.h>//for fork
# include <sys/stat.h> //for stat in access check
# include <sys/types.h>//for pid_t
# include <fcntl.h>//for file open flags
# include <stdbool.h>
# include <stddef.h>
# include <signal.h>

extern volatile __sig_atomic_t g_sig;

# include "define.h"

typedef enum e_do_err 
{
    ERRNO 	= 0b00001,
	EXTRARG = 0b00010,
    LOG   	= 0b00100,
    CLEAN 	= 0b01000,
    EXIT  	= 0b10000
} t_do_err;

typedef enum e_redirect_type
{
	REDIR_NONE,
    REDIR_HDOC,
	REDIR_INP,
	REDIR_OUTP,
	REDIR_APPEN,
}   t_redir_type;

typedef struct s_redir
{
    t_redir_type    type;//ambiguoous redir. If it comes from expansion and has space then it is ambiguous redirection. also if NULL
    char    *fname_o_del;
	int		expan;
    struct s_redir *next;
}   t_redir;

typedef struct s_errnote
{
	char *cmd_path;
	char *strerr;
}	t_errnote;

typedef struct s_cmd
{
	char		**cmd;
	int			hdoc_st_pos;
	t_errnote	err_note;
    t_redir     *redir;
} t_cmd;

typedef struct s_expan
{
	char *tok;
	char *suffix;
	char *prefix;
	char *exp;
	char *key;
	char **cur_exp_arr;
	char **exp_arr;
	int exp_arr_len;
	int	newtok_offset;
} t_expan;

typedef struct s_token
{
    char    		*token;
	t_redir_type	redir;
    char    		**expand;
} t_token;

typedef struct s_parse
{
    char        **seg;
    t_token     **token;
}   t_parse;

typedef struct s_msh
{
	char	*cwd;
	char	*old_wd;
	char	*prompt;
	char	**envl;
	t_parse *aux;
	t_cmd	**cmd;
	int		cmd_count; //  for command.c
	int		hdocfd_l[HEREDOC_MAX];
	int		exit_code;
} t_msh;

# include "../lib/libft/libft.h"


void msh_init(t_msh *msh);
void	msh_parse(char *line, t_msh *msh);
void print_segments(char **seg);
void init_parse_structs(t_msh *msh, char *line);
void	init_token(t_msh *msh, int cmd_count);
int	count_pipes(char *line);
void line_split_bypipe(t_msh *msh, char *line, char **seg_arr);
int	 check_quotes(char *start, char *curr);
void	seg_tokenize(t_msh *msh, t_parse *aux);
void extract_token(t_msh *msh, t_token **token, char *seg);
void skip_whitespaces(char **str);
void	*ft_realloc(void *ptr, size_t size_prev, size_t size_new);
int get_token_len(char *seg, t_token *token, int tok_len);
int set_redir_type(t_token *token, char *seg);


void expand_and_setup_cmd(t_msh *msh, t_token **token);
void expscan_token(t_msh *msh, t_token token);
void expscan_token(t_msh *msh, t_token token);
char *extract_env_key(char **token);
void init_exp(t_msh *msh, t_token token, t_expan *exp);



//cd
void    builtin_cd(t_msh *msh, char **cmd);
void    cd_path(t_msh *msh, char *path);
void    cd_tilde(t_msh *msh, char *tilde_path);
void    cd_env_var(t_msh *msh, char *dir);
void    msh_wd_update(t_msh *msh);
void    handle_unlinked_cwd(t_msh *msh, char *path);

//echo
void    builtin_echo(t_msh *msh, char **cmd);

//env
void    builtin_env(t_msh *msh, char **cmd);

//exit
void    builtin_exit(t_msh *msh, char **cmd);
int is_numeric(char *str);

//export
void    builtin_export(t_msh *msh, char **cmd);
int is_valid_id(char *x_var);

//pwd
void    builtin_pwd(t_msh *msh);

//unset
void    builtin_unset(t_msh *msh, char **cmd);
void    unset_env(t_msh *msh, char **envl, char *key);

//exec_builtin
void execin_shell(t_msh *msh, char **cmd);
void exec_builtin(t_msh *msh, char **cmd);
int is_builtin(char **cmd);



//execute
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



//envp
void	duplicate_env(t_msh *msh, char **envp);
void	generate_mini_env(t_msh *msh);
void	set_shlvl(t_msh *msh, char **envl);

char    *get_env(char **envl, char *var);
void    update_env(t_msh *msh, char *key, char *value);
void    set_env(t_msh *msh, char **envl, char *entry);
void    add_env_var(t_msh *msh, char **envl, char *entry);
void    overwrite_env_var(t_msh *msh, char **env_var, char *entry);



void	sigint_handler(int sig);
void	sig_handler_child(int sig);
void	sig_handler_heredoc(int signum);
void	init_sig(void);
void	sig_handler_changer(void);
void	sig_reseted(void);
void	sig_heredoc(void);
//# include "envp.h"

//# include "parse.h"
//# include "envp.h"
///# include "execute.h"
//# include "builtin.h"


/* void msh_init(t_msh *msh, char **envp);
void	msh_loop(t_msh *msh);
//void	msh_clean(t_msh *msh);
int err_out(char *msg); */

#endif