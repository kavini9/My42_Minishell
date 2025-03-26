/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:00:53 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/25 17:47:40 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * initialize_token - Initializes the fields of a token structure.
 *
 * @token: Pointer to the token structure to initialize.
 *
 * Sets all fields of the token structure to their initial values:
 * `NULL` for pointers, `0` for integers, and `-1` for file descriptors.
 * This ensures a clean state before populating the structure.
 */
void initialize_token(t_token *token)
{
    token->command = NULL;           // Initialize the token name as NULL
    token->command_path = NULL;           // Initialize the token path as NULL
    token->token_index = 0;             // Initialize the token index to 0
    token->token_args = NULL;           // Initialize the token arguments as NULL
    token->token_arg_count = 0;         // Initialize the argument count to 0
    token->redir_start = NULL;          // Initialize the first redirection as NULL
    token->redir_end = NULL;            // Initialize the last redirection as NULL
    token->input_fd = -1;               // Initialize the input file descriptor to -1 (no redirection)
    token->output_fd = -1;              // Initialize the output file descriptor to -1 (no redirection)
    token->token_exit_status = 0;       // Initialize the exit status to 0
}

/**
 * count_pipes - Counts the number of pipe symbols in the given line.
 *
 * @line: The input command line.
 *
 * Iterates through the input line and counts occurrences of the '|' character,
 * ensuring they are not inside quotes.
 *
 * Returns: The number of pipes found.
 */
int count_pipes(char *line)
{
    int i;
    int pipe_count;

    i = 0;
    pipe_count = 0;
    while (line[i])
    {
        if (line[i] == '|' && !check_quotes(line, i))
            pipe_count++;
        i++;
    }
    return (pipe_count);
}

/**
 * allocate_token_structs - Allocates and initializes token structures.
 *
 * @msh: Pointer to the shell structure containing the token array.
 * @token_count: The total number of tokens to allocate.
 *
 * Iterates through the `msh->tokens` array, allocating memory for each
 * token structure and initializing it using `initialize_token`.
 * If allocation fails, frees previously allocated memory and returns 1.
 *
 * Returns: 0 on success, or 1 on allocation failure.
 */
static int allocate_token_structs(t_msh *msh, int token_count)
{
    int i;
    i = 0;
    while (i < token_count)
    {
        msh->tokens[i] = malloc(sizeof(t_token));
        if (!msh->tokens[i])
        {
            ft_putendl_fd("Failed to allocate memory for struct", 2);
            clean_tokens(msh->tokens);  // Assuming `clean_tokens` frees memory properly
            return (1);
        }
        initialize_token(msh->tokens[i]);
        i++;
    }
    msh->tokens[token_count] = NULL;
    return (0);
}

/**
 * build_token_structs - Prepares the array of token structures.
 *
 * @msh: Pointer to the shell structure containing the token details.
 * @line: The input line to process.
 *
 * Calculates the number of tokens based on the pipe count in the input
 * line and allocates memory for the token array. Calls `allocate_token_structs`
 * to allocate and initialize individual token structures.
 *
 * Returns: 0 on success, or 1 if memory allocation fails.
 */
int build_token_structs(t_msh *msh, char *line)
{
    int token_count;

    token_count = count_pipes(line) + 1;
    msh->cmd_count = token_count;
    msh->tokens = ft_calloc(token_count, sizeof(t_token));
    if (!msh->tokens)
    {
        ft_putendl_fd("Failed to allocate memory for token array", 2);
        return (1);
    }
    if (allocate_token_structs(msh, token_count))
        return (1);
    return (0);
}
