#ifndef PARSE_H
#define PARSE_H

# include "../../lib/libft/libft.h"

# include <stdbool.h>
# include <readline/readline.h> // for readline
# include <readline/history.h>  // for add_history function
# include <stdio.h>             // temporary printf in msh_clean (delete later if unnecessary)
# include <stdlib.h>            // for exit
# include <string.h>            // for strerror(errnum)
# include <errno.h>             // for using errno in strerror
# include <signal.h>            // for signal handling
// #include "../../includes/minishell.h"  // Ensure t_msh and other necessary types are included
extern int g_sig;

/**
 * Structure representing a parsed command.
 */
typedef struct s_cmd
{
    char          **args;      // Array of command arguments
    int           cmd_index;   // Index of the command in the pipeline
    struct s_cmd *next;        // Pointer to the next command in the pipeline
} t_cmd;

// Function Prototypes

// Whitespace and syntax checks
int  check_redirects(char *line, t_msh *msh);
int  check_quotes(char *line, int length);
int  skip_whitespace(char *str, int i);
int  ft_isspace(char c);
int  validate_pipe(char **line, t_msh *msh);
int is_input_empty(const char *input);
int handle_unmatched_quotes(char **line);

// Parsing input and command handling
int  msh_parse(char **line, t_msh *msh);
int  validate_input_syntax(char **input, t_msh *msh);
int  parse_input(t_msh *msh);
int  parse_cmd_string(t_msh *msh, t_cmd *cmd);
int  cmd_string_while(t_msh *msh, t_cmd *cmd, int i, int *cmd_found);
int validate_input(char **line, t_msh *msh);

// Command list management
void add_cmd(t_msh *msh, char **args);
t_cmd *create_cmd(char **args);
void free_cmd_list(t_cmd *cmd_list);

// Handling trailing input and signals
char *get_trailing_input(t_msh *msh, char *line);
void  sigint_handler(int sig);
void  sig_handler_heredoc(int sig);
void  sig_handler_hd(int sig);

int check_redirects(char *line, t_msh *msh);
static int check_in_redir(char *line, t_msh *msh, int *i);
static int check_out_redir(char *line, t_msh *msh, int *i);
static int validate_redirect(char *line, t_msh *msh, int *i, char *type);

// External global variable (ensure it is defined elsewhere)
//extern int g_sig;

#endif
