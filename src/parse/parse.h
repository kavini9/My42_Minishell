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
#include <stddef.h>  // For NULL
#include "../../includes/minishell.h"  // Ensure t_msh and other necessary types are included

extern int g_sig;

/**
 * Structure representing a parsed command token.
 */
typedef struct s_token
{
    char    *seg;
    char    *token_name;          // Name of the token (e.g., "ls", "echo")
    char    *token_path;          // Path to the token (e.g., "/bin/ls")
    int     token_index;          // Index for the token in a pipeline
    char    **token_args;         // Array of arguments passed to the token
    int     token_arg_count;      // Number of arguments
    void    *redir_start;         // First redirection (could be file path or other structure)
    void    *redir_end;           // Last redirection (could be file path or other structure)
    int     input_fd;             // File descriptor for input redirection
    int     output_fd;            // File descriptor for output redirection
    int     token_exit_status;    // Exit status of the token
    struct s_token *next;         // Pointer to the next token in the pipeline
} t_token;

// Token functions
void clean_tokens(t_token **tokens);                      // Cleans up allocated memory for token structures
int build_token_structs(t_msh *msh, char *input);         // Builds token structures from the input
int allocate_token_structs(t_msh *msh, int token_count);  // Allocates and initializes token structures
void initialize_token(t_token *token);                    // Initializes a token structure
int count_pipes(char *line);                              // Counts the number of pipe symbols in the input

// New functions added for line splitting
char *trim_whitespace(char *seg); // Trims leading and trailing whitespace from a string
int segment_handler(t_token *token, char *line, int start, int end); // Handles extracting and trimming segments
int split_line(char *line, t_msh *msh); // Splits the line into tokens, respecting quoted pipes

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
int  parse_cmd_string(t_msh *msh, t_token *token);
int  cmd_string_while(t_msh *msh, t_token *token, int i, int *cmd_found);
int validate_input(char **line, t_msh *msh);

// Command list management
void add_cmd(t_msh *msh, char **args);
t_token *create_cmd(char **args);
void free_cmd_list(t_token *cmd_list);

// Handling trailing input and signals
char *get_trailing_input(t_msh *msh, char *line);
void  sigint_handler(int sig);
void  sig_handler_heredoc(int sig);
void  sig_handler_hd(int sig);

int check_redirects(char *line, t_msh *msh);
static int check_in_redir(char *line, t_msh *msh, int *i);
static int check_out_redir(char *line, t_msh *msh, int *i);
static int validate_redirect(char *line, t_msh *msh, int *i, char *type);

#endif
