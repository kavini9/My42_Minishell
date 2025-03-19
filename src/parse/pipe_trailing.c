/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_trailing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:50:10 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/19 18:07:59 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/**
 * finalize_pipe_processing - Restores input state and finalizes handling.
 *
 * @msh: Shell structure managing shell state.
 * @line: Processed input string to be returned.
 *
 * Restores the shell state and ensures proper cleanup.
 *
 * Return: The processed input string, or NULL on failure.
 */

 
/* static char *finalize_pipe_processing(t_msh *msh, char *line)
{
    // Restore the shell state and perform cleanup.
    if (restore_and_cleanup(msh, 0, 0) != 0)
    {
        free(line); // Free the input line if cleanup fails.
        return (NULL);
    }
    return (line); // Return the processed input line.
} */



/**
 * concat_and_cleanup - Concatenates two strings and frees original inputs.
 *
 * @msh: Shell structure managing shell state.
 * @line: Original input string.
 * @additional_input: Newly captured input string.
 *
 * This function joins `line` and `additional_input`,
 * then frees both input strings. If allocation fails,
 * it ensures proper cleanup of shell resources.
 *
 * Return: The concatenated string, or NULL on failure.
 */
static char *concat_and_cleanup(t_msh *msh, char *line, char *additional_input)
{
    char *updated_input;

    // Concatenate the two input strings.
    updated_input = ft_strjoin(line, additional_input);
    free(additional_input); // Free the additional input string.
/* 
    // Check if concatenation failed.
    if (!updated_input)
    {
        msh->exit_code = restore_and_cleanup(msh, 0, 1); // Cleanup on failure.
        free(line); // Free the original input line.
        return (NULL);
    }

    // Cleanup and return the concatenated string.
    msh->exit_code = restore_and_cleanup(msh, 0, 0);
    free(line); // Free the original input line.
    return (updated_input); */
	    
	// Cleanup and return the concatenated string.
	msh->exit_code = 2;
	free(line); // Free the original input line.
	return (updated_input);
}

/**
 * get_trailing_input - Retrieves additional input from the user.
 *
 * @msh: Pointer to the shell's main structure.
 * @line: The initial line of input.
 *
 * This function allows for multi-line input, continuing to read lines
 * until a valid input is provided. It handles interruptions like SIGINT (Ctrl+C).
 * If an empty input is provided, the function will prompt again.
 * If interrupted, it will clean up and return NULL.
 *
 * Return: The concatenated input line if valid input is provided, or NULL if interrupted or invalid.
 */
char *get_trailing_input(t_msh *msh, char *line)
{
    char *additional_input;

    additional_input = NULL; // Initialize a pointer to store additional user input.

    // Set a signal handler for SIGINT (Ctrl+C).
    signal(SIGINT, sig_handler_hd);

    // Enter an infinite loop to keep reading additional input.
    while (1)
    {
        // Prompt the user for additional input.
        additional_input = readline("> ");

        // Handle interruptions or empty input.
        if (!additional_input || g_sig == SIGINT)
        {
            g_sig = 0; // Reset the global signal flag.
           // msh->exit_code = restore_and_cleanup(msh, -1, 1); // Cleanup on interruption.
		   	msh->exit_code = 2;
            free(line); // Free the initial input line.
            return (NULL); // Return NULL to indicate interruption.
        }

        // If the additional input is not empty, concatenate it with the initial line.
        if (!is_input_empty(additional_input))
            return (concat_and_cleanup(msh, line, additional_input));

        // If the additional input is empty, free it and prompt again.
        free(additional_input);
    }

    /* // Finalize processing and return the result.
    return (finalize_pipe_processing(msh, line)); */
	return (line);
}
