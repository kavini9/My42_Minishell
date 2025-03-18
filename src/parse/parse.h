#ifndef PARSE_H
#define PARSE_H

# include "../../lib/libft/libft.h"

#include <stdbool.h>


# include <readline/readline.h> //for readline
# include <readline/history.h> //for readline add_history function
# include <stdio.h> //temporary printf in msh_clean. delete later if you use your own
# include <stdlib.h> //for exit
# include <string.h> //for strerror(errnum)
# include <errno.h> //for using errno in strerror
#include <signal.h>
//#include "../../includes/minishell.h"  // Ensure t_msh and other necessary types are included

/**
 * Structure representing a parsed command.
 */
typedef struct s_cmd
{
    char          **args;      // Array of command arguments
    int           cmd_index;   // Index of the command in the pipeline
    struct s_cmd *next;        // Pointer to the next command in the pipeline
} t_cmd;



typedef struct s_msh
{
	char	*cwd;
	char	*old_wd;
	char	*prompt;
	int		exit_code;
	char	**envl;
//	t_token	*tokenl;
} t_msh;
// Function Prototypes
int check_redirects(char *line, t_msh *msh);
int check_quotes(char *line, int length);
int	skip_whitespace(char *str, int i);
int ft_isspace(char c);
int validate_pipe(char **line, t_msh *msh);

/**
 * Parses and validates the user input.
 * - Splits input into commands.
 * - Checks for syntax errors.
 */
int parse_and_validate_input(char **input, t_msh *msh);

/**
 * Validates input syntax.
 * - Checks for unmatched quotes, invalid pipes, and improper redirections.
 */
int validate_input_syntax(char **input, t_msh *msh);

/**
 * Parses the input into structured command objects.
 */
int parse_input(t_msh *msh);

/**
 * Parses a command string and stores parsed tokens into the command structure.
 */
int parse_cmd_string(t_msh *msh, t_cmd *cmd);

/**
 * Processes command parsing loop.
 * - Handles command tokenization.
 * - Ensures correct parsing logic.
 */
int cmd_string_while(t_msh *msh, t_cmd *cmd, int i, int *cmd_found);

/**
 * Adds a command to the command list.
 */
void add_cmd(t_msh *msh, char **args);

/**
 * Creates a new command structure with given arguments.
 */
t_cmd *create_cmd(char **args);

/**
 * Frees allocated memory for the command list.
 */
void free_cmd_list(t_cmd *cmd_list);

#endif
