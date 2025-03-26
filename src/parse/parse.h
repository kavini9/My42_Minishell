#ifndef PARSE_H
#define PARSE_H

# include "../../lib/libft/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>      // for debugging, can be removed later
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stddef.h>
# include "../../includes/minishell.h"  // t_msh and other shared structures

extern int g_sig;

/**
 * Structure representing a parsed command token.
 */
typedef struct s_token
{
    char    *seg;                // Raw segment string from user input
    char    *command;            // Command name (e.g., "ls", "echo")
    char    *command_path;       // Full path to command (e.g., "/bin/ls")
    int     token_index;         // Index in the pipeline (0, 1, ...)
    char    **args;        // Command arguments
    int     arg_count;     
    void    *redir_start;        // Pointer to first redirection
    void    *redir_end;          // Pointer to last redirection
    int     input_fd;            
    int     output_fd;           
    int     token_exit_status;   
    struct s_token *next;        // Linked list pointer (not always used)
} t_token;

// Token functions
void clean_tokens(t_token **tokens);
int build_token_structs(t_msh *msh, char *input);
int allocate_token_structs(t_msh *msh, int token_count);
void initialize_token(t_token *token);
int count_pipes(char *line);

// Splitting and segment handling
char *trim_whitespace(char *seg);
int segment_handler(t_token *token, char *line, int start, int end);
int split_line(char *line, t_msh *msh);

// Syntax and validation
int check_redirects(char *line, t_msh *msh);
int check_quotes(char *line, int length);
int skip_whitespace(char *str, int i);
int ft_isspace(char c);
int validate_pipe(char **line, t_msh *msh);
int is_input_empty(const char *input);
int handle_unmatched_quotes(char **line);

// Parsing input and commands
int msh_parse(char **line, t_msh *msh);
int validate_input_syntax(char **input, t_msh *msh);
int parse_input(t_msh *msh);
int parse_cmd_string(t_msh *msh, t_token *token);
int cmd_string_while(t_msh *msh, t_token *token, int i, int *cmd_found);
int validate_input(char **line, t_msh *msh);

// Command list management
void add_cmd(t_msh *msh, char **args);
t_token *create_cmd(char **args);
void free_cmd_list(t_token *cmd_list);

// Signal handling
char *get_trailing_input(t_msh *msh, char *line);
void sigint_handler(int sig);
void sig_handler_heredoc(int sig);
void sig_handler_hd(int sig);

#endif
