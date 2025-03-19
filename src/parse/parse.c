/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:53:36 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/19 17:56:12 by aoshinth         ###   ########.fr       */
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
 * Handles unmatched quotes by allowing multiline input.
 * If the user presses Ctrl+D (EOF), it exits gracefully without an error.
 */
int handle_unmatched_quotes(char **line)
{
    char *extra_line;
    char *temp;

    // Keep asking for more input if quotes are unmatched
    while (check_quotes(*line, ft_strlen(*line)))
    {
        extra_line = readline(">"); // Read additional user input

        // If user presses Ctrl+D (EOF), just exit gracefully without an error
        if (!extra_line)
            return (0);

        // Append a newline character to the existing input
        temp = *line;
        *line = ft_strjoin(*line, "\n");
        free(temp);

        // Append the new input to the existing input line
        temp = *line;
        *line = ft_strjoin(*line, extra_line);
        free(temp);
        free(extra_line);
    }
    return (0);
}

/**
 * Validates the input for syntax errors.
 * - Checks for unmatched quotes (calls handle_unmatched_quotes)
 * - Validates pipes, semicolons, and backslashes
 * - Ensures correct redirection syntax
 * Returns 1 if an error is found, otherwise returns 0.
 */
int validate_input(char **line, t_msh *msh)
{
    int i;

    // Allow multi-line input if quotes are unmatched
    handle_unmatched_quotes(line);

    // Validate pipe usage (e.g., ensuring pipes aren't misused)
    if (validate_pipe(line, msh))
        return (1);

    // Loop through the input string to check for invalid characters
    i = 0;
    while ((*line)[i])
    {
        // Ensure characters like ';' and '\' are not used improperly
        if (!check_quotes(*line, i) && ((*line)[i] == ';' || (*line)[i] == '\\'))
        {
            ft_putendl_fd("invalid syntax", 2); // Print error message
            msh->exit_code = 2; // Set exit code
            return (1);
        }
        i++;
    }

    // Validate redirections (e.g., checking if `>` or `<` is used correctly)
    return check_redirects(*line, msh);
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
int msh_parse(char **line, t_msh *msh)
{
    // Validate user input for syntax errors
    if (validate_input(line, msh))
        return (1);

    /* // Prepare command structures for execution
    if (prepare_command_structs(shell, *line))
        return (1);

    // Split input into commands based on pipes
    if (split_input_by_pipes(*line, shell))
        return (1);

    // Parse commands into structured format for execution
    if (parse_input(shell))
        return (1); */

    return (0);
}



