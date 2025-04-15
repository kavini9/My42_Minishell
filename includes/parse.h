/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:24:31 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/15 18:03:15 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

/**
 * @file parse.h
 * @brief Header for parsing and input validation in Minishell.
 *
 * Contains struct definitions and function declarations related to
 * command parsing, validation, expansion, redirections, heredocs,
 * and quote/variable processing.
 */

# include "minishell.h"
/* # include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
#include <fcntl.h>

# include <stddef.h> */


# define TMP_S "/tmp/heredoc"
# define TMP_EXT ".tmp"


typedef struct s_env
{
	char			*name;
	struct s_env	*next;
	char			*value;

}	t_env;

/* ────────────────────────────────────────────────────────────── */
/*                       ENUMERATIONS                             */
/* ────────────────────────────────────────────────────────────── */

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
} t_redir_type;

/**
 * s_hd - Structure for heredoc-related metadata.
 *
 * Members:
 * - cmd_str: Command identifier string.
 * - heredoc_str: Heredoc-specific identifier string.
 * - base: Base string for heredoc file naming.
 * - mid: Intermediate string for heredoc file naming.
 * - full: Full string for the heredoc file path.
 */
typedef struct s_hd
{
	char	*cmd_str;
	char	*heredoc_str;
	char	*base;
	char	*mid;
	char	*full;
}	t_hd;



/* ────────────────────────────────────────────────────────────── */
/*                     STRUCTURES                                 */
/* ────────────────────────────────────────────────────────────── */

typedef struct s_vdata
{
	char	*value;
	char	**expan;
	char	*temp;
	char	*name;
} t_vdata;

typedef struct s_expand
{
	int		sgl;
	int		dbl;
	int		i;
	char	*name;
	char	*value;
	int		start;
} t_expand;

typedef struct s_redir
{
	char			*file;
	char			*delimiter;
	t_redir_type	type;
	bool			expand;
	char			*heredoc_name;
	int				heredoc_index;
	struct s_redir	*next;
} t_redir;

typedef struct s_cmd
{
	char		*seg;
	char		*command;
	char		**cmd;
	int			cmd_index;
	t_redir		*redir_start;
	t_redir		*redir_end;
	int			input_fd;
	int			output_fd;
	int			cmd_exit_status;
	struct s_cmd *next;
} t_cmd;

typedef struct s_msh
{
	int		cmd_count;
	char	*cwd;
	t_env	*env;
	char	*old_wd;
	char	*prompt;
	char	**envl;
	t_cmd	*cmds;
	char		**pending;
	int		**pipes;
	int		exit_code;
	int		stdin_saved;
	int		stdout_saved;
} t_msh;

/* ────────────────────────────────────────────────────────────── */
/*                COMMAND ALLOCATION & INITIALIZATION            */
/* ────────────────────────────────────────────────────────────── */

void	clean_cmds(t_cmd *cmd_list);
int		build_command_structs(t_msh *msh, char *input);
int		allocate_token_structs(t_msh *msh, int token_count);
void	initialize_token(t_cmd *token);
int		count_pipes(char *line);

/* ────────────────────────────────────────────────────────────── */
/*                   LINE SPLITTING & SEGMENTS                   */
/* ────────────────────────────────────────────────────────────── */

char	*trim_whitespace(char *seg);

int		split_line_by_pipe(char *line, t_msh *msh);

/* ────────────────────────────────────────────────────────────── */
/*                      REDIRECTION CHECKING                     */
/* ────────────────────────────────────────────────────────────── */

int		check_redirects(char *line, t_msh *msh);
int		validate_redirect(char *line, t_msh *msh, int *i, char *type);
int		we_have_heredoc(t_expand *arg, char *str, int n);
void	unlink_all_heredocs(t_msh *msh);

/* ────────────────────────────────────────────────────────────── */
/*                     SYNTAX & PIPE VALIDATION                  */
/* ────────────────────────────────────────────────────────────── */

int		check_quotes(char *line, int length);
int		skip_whitespace(char *str, int i);
int		ft_isspace(char c);
int		validate_pipe(char *line, t_msh *msh);
int		is_input_empty(const char *input);
int		handle_unmatched_quotes(char *line);
int		validate_input(char *line, t_msh *msh);
int		validate_input_syntax(char *input, t_msh *msh);

/* ────────────────────────────────────────────────────────────── */
/*                       PARSING PIPELINE                        */
/* ────────────────────────────────────────────────────────────── */

int		msh_parse(char *line, t_msh *msh);
int		parse_input(t_msh *msh);
int		parse_cmd_string(t_msh *msh, t_cmd *token);
int		cmd_string_while(t_msh *msh, t_cmd *token, int i, int *cmd_found);
int		parse_line(t_msh *msh);
int		no_args(t_cmd *cmd, int i);
int		handle_cmd_name(t_cmd *cmd, int i);
int		handle_cmd_args(t_msh *msh, t_cmd *cmd, int i);

/* ────────────────────────────────────────────────────────────── */
/*               ARGUMENT EXTRACTION UTILITIES                   */
/* ────────────────────────────────────────────────────────────── */

int		init_args_array(t_cmd *cmd, int i);
int		count_args(t_cmd *cmd, int i);
int		count_if_redirection(t_cmd *cmd, int i);
int		only_redirect(char *str, int i);
int		append_to_array(t_cmd *cmd, char *arg, int *index);
int		arg_no_quotes(t_cmd *cmd, t_expand *arg, int i);
int		arg_in_quotes(char *str, int i, t_expand *arg);

/* ────────────────────────────────────────────────────────────── */
/*                  EXPANSION & QUOTE HANDLING                   */
/* ────────────────────────────────────────────────────────────── */

int		handle_expand(t_msh *msh, t_cmd **token);
int		init_expansion(t_expand *arg, char **expan);
int		the_arg(t_expand *arg, int i);
void	what_quote(char *str, t_expand *arg);
int		handle_question(t_msh *msh, char *str, char **expan, t_expand *arg);
int		new_result(t_expand *arg, char *temp);
int		oh_a_dollar(t_msh *msh, char *str, char **expan, t_expand *arg);
int		we_have_dollar(t_msh *msh, t_expand *arg, char *str);
int		tildes_home(t_msh *msh, char *str, char **expan, t_expand *arg);
int		handle_value(t_msh *msh, t_vdata *data);
char	*ft_strjoin_char(char *str, char c);
void	just_a_quest(char *str, char *name, int *indx, t_expand *arg);
void	we_need_name(t_expand *arg, char *str, char *name, int *indx);
int		s_unquoted(t_msh *msh, t_cmd **cmd, t_expand *arg, char **expan);
int		no_quotes(t_msh *msh, t_cmd *cmd, int i, t_expand *arg);

/* ────────────────────────────────────────────────────────────── */
/*                 COMMAND LIST MANAGEMENT                       */
/* ────────────────────────────────────────────────────────────── */

void	add_cmd(t_msh *msh, char **args);
t_cmd	*create_cmd(char **args);
void	free_cmd_list(t_cmd *cmd_list);

/* ────────────────────────────────────────────────────────────── */
/*                   SIGNAL HANDLING                             */
/* ────────────────────────────────────────────────────────────── */

void	init_sig(void);
void	sig_handler_changer(void);
void	sig_reseted(void);
void	sig_heredoc(void);
void	sigint_handler(int sig);
void	sig_handler2(int sig);
void	sig_handler_heredoc(int sig);
void	sig_handler_hd(int sig);

void	ft_free_array(char **array);
void	clean_redir(t_redir *head);
int in_quotes(t_msh *msh, char *str, int i, t_expand *arg);
int	add_char(char *str, t_expand *arg);
int no_expanding(t_msh *msh, char *str, t_expand *arg);
char	*ft_strndup(const char *src, size_t n);
bool is_redirection(t_cmd *cmd, int i);
int handle_redirections(t_msh *msh, t_cmd *cmd, int i);
int	redirll_head_tail(t_cmd *cmd);
void	redir_lstadd_back(t_redir **lst, t_redir *new);
int handle_heredoc(t_msh *msh, t_cmd *cmd, int i);
int handle_append(t_cmd *cmd, int i);
int handle_redirect_in(t_cmd *cmd, int i);
int handle_redirect_out(t_cmd *cmd, int i);
int	filename_in_quotes(t_cmd *cmd, char *str, int i, t_expand *arg);
int	parse_filename(t_cmd *cmd, int i, char **filename);
int generate_hd_file(t_cmd *cmd);
int	check_expand(t_msh *msh, t_cmd *cmd, char **line, int fd);
int	heredoc_expander(t_msh *msh, char **line);
void	close_all_pipes(t_msh *msh);
void	hd_free(t_expand *arg, char *expan);
void	clean_cmd_unlink(t_msh *msh);
void	exit_for_success(t_msh *msh, int i, int exit_status);
void	exit_for_failure(t_msh *msh, int i, int exit_status);
void	clean_env(t_env *ll, char **array);
void	error(t_msh *msh, char *str);
void	ft_free_int_arr_with_size(int **array, int size);
int	open_and_write_to_heredoc(t_msh *msh, t_cmd *cmd);
char *get_trailing_input(t_msh *msh, char *line);

#endif // PARSE_H