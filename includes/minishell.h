/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/27 22:18:00 by wweerasi         ###   ########.fr       */
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