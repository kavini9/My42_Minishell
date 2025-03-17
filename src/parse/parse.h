#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>

typedef struct s_cmd
{
    char            **args;
    int             cmd_index;
    struct s_cmd   *next;
} t_cmd;



// Function Prototypes
int     parse_and_validate_input(char **input, t_shell *mini);
int     validate_input_syntax(char **input, t_shell *mini);
int     parse_input(t_shell *mini);
int     parse_cmd_string(t_shell *mini, t_cmd *cmd);
int     cmd_string_while(t_shell *mini, t_cmd *cmd, int i, int *cmd_found);
void    add_cmd(t_shell *mini, char **args);
t_cmd   *create_cmd(char **args);

#endif
