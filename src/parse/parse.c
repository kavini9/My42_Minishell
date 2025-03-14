/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:53:36 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/14 17:56:32 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * validate_input - Checks the syntax of the user input.
 * @line: Pointer to the input string entered by the user.
 * @shell: Pointer to the shell structure.
 *
 * This function performs the following checks:
 * - Ensures all quotes are properly matched.
 * - Validates the correct usage of pipes (`|`).
 * - Prevents the use of invalid characters like `;` and `\`.
 * - Verifies correct redirection syntax.
 *
 * If any syntax errors are found, the function prints an error message,
 * sets the shell's exit status to an error value, and returns 1.
 *
 * Returns:
 * - 0 if the input is valid.
 * - 1 if a syntax error is detected.
 */
int validate_input(char **line, t_shell *shell)
{
    int i;

    // Check for unmatched quotes in the input
    if (check_quotes(*line, ft_strlen(*line)))
    {
        ft_putendl_fd("syntax error: unmatched quotes", 2);
        shell->exit_stat = 2;
        return (1);
    }

    // Validate pipe usage
    if (validate_pipe (line, shell))
        return (1);

    i = 0;
    while ((*line)[i])
    {
        // Ensure characters like ';' and '\' are not improperly used
        if (!check_quotes(*line, i) && ((*line)[i] == ';' || (*line)[i] == '\\'))
        {
            ft_putendl_fd("invalid syntax", 2);
            shell->exit_stat = 2;
            return (1);
        }
        i++;
    }

    // Check for correct redirection syntax
    if (check_redirects(*line, shell))
        return (1);

    return (0);
}

/**
 * validate_and_parse - Validates and processes user input for execution.
 * @line: Pointer to the user input string.
 * @shell: Pointer to the shell structure.
 *
 * This function:
 * - Calls `validate_input` to check for syntax errors.
 * - Prepares command structures if validation succeeds.
 * - Splits the input into separate commands based on pipes (`|`).
 * - Calls `parse_input` to further process the structured commands.
 *
 * If any stage fails, the function returns an error.
 *
 * Returns:
 * - 0 if parsing is successful.
 * - 1 if any error occurs during validation or parsing.
 */
int validate_and_parse(char **line, t_shell *shell)
{
    // Validate user input for syntax errors
    if (validate_input(line, shell))
        return (1);

    // Prepare command structures for execution
    if (prepare_command_structs(shell, *line))
        return (1);

    // Split input into commands based on pipes
    if (split_input_by_pipes(*line, shell))
        return (1);

    // Parse commands into structured format for execution
    if (parse_input(shell))
        return (1);

    return (0);
}



