/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:24:31 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/04 19:08:57 by aoshinth         ###   ########.fr       */
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

# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stddef.h>
# include "minishell.h"

extern volatile sig_atomic_t g_signal;

/* ────────────────────────────────────────────────────────────── */
/*                       ENUMERATIONS                             */
/* ────────────────────────────────────────────────────────────── */

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_redir_type;

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
	void		*redir_start;
	void		*redir_end;
	int			input_fd;
	int			output_fd;
	int			cmd_exit_status;
	struct s_cmd *next;
} t_cmd;

typedef struct s_msh
{
	int		cmd_count;
	char	*cwd;
	char	*old_wd;
	char	*prompt;
	char	**envl;
	t_cmd	*cmds;
	int		exit_code;
} t_msh;

/* ────────────────────────────────────────────────────────────── */
/*                TOKEN ALLOCATION & INITIALIZATION              */
/* ────────────────────────────────────────────────────────────── */

void	clean_tokens(t_cmd **tokens);
int		build_command_structs(t_msh *msh, char *input);
int		allocate_token_structs(t_msh *msh, int token_count);
void	initialize_token(t_cmd *token);
int		count_pipes(char *line);

/* ────────────────────────────────────────────────────────────── */
/*                   LINE SPLITTING & SEGMENTS                   */
/* ────────────────────────────────────────────────────────────── */

char	*trim_whitespace(char *seg);
int		segment_handler(t_cmd *token, char *line, int start, int end);
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

char	*get_trailing_input(t_msh *msh, char *line);
void	sigint_handler(int sig);
void	sig_handler_heredoc(int sig);
void	sig_handler_hd(int sig);

#endif // PARSE_H
