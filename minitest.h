#ifndef MINITEST_H
# define MINITEST_H

# define  HEREDOC_MAX 16

# define X_KO 126
# define F_KO 127
#define IS_DIRECTORY "Is a directory" 
# define CMD_NOT_FOUND "command not found"

# include "lib/libft/libft.h"
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
# include <sys/wait.h>

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
	char **tmp_arr;
	char **exp_arr;
	int exp_arr_len;
	int	scan_offset;
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


void msh_init(t_msh *msh, char **envp);
void    msh_parse(t_msh *msh, char *line);
void print_segments(char **seg);
void init_parse_structs(t_msh *msh, char *line);
void	init_token(t_msh *msh, int cmd_count);
int	count_pipes(char *line);
void line_split_bypipe(t_msh *msh, char *line, char **seg_arr);
int	 check_quotes(char *start, char *curr);
void	seg_tokenize(t_msh *msh, t_parse *aux);
void extract_token(t_msh *msh, t_token **token, char *seg);
void skip_whitespaces(char **str);
int get_token_len(char *seg, t_token *token, int tok_len);
int set_redir_type(t_token *token, char *seg);
int redir_skip(char *seg);


void init_exp(t_msh *msh, t_token token, t_expan *exp);
void revise_exp_arr(t_msh *msh, t_token *token, t_expan *exp);
char *extract_env_key(char **token);
void    get_tmp_arr(t_msh *msh, t_expan *exp, char *exp_dup, int q_context);
size_t	ft_arrlen(void **arr);
void    concat_exp_edge(t_msh *msh, t_expan *exp, int spc, int index);
void    extend_exp_edge(t_msh *msh, t_expan *exp, int index, int *len);
void    adjust_exp_edge(t_msh *msh, t_expan *exp, char *exp_val, int q_context);
void    expand_parameter(t_msh *msh, t_token *token, t_expan *exp);
void expscan_token(t_msh *msh, t_token *token);
void expand_tokens(t_msh *msh, t_token **token);