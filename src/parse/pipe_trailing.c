/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_trailing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:50:10 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/14 19:01:00 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * process_trailing_pipe - Handles commands ending with a pipe (`|`).
 *
 * @shell: Pointer to the shell structure managing state information.
 * @line: Current input string to be extended.
 *
 * This function deals with cases where the input ends with
 * a trailing pipe (`|`), meaning additional input is needed.
 * It continuously prompts the user with a secondary prompt (`>`)
 * until a valid input is received or the operation is canceled.
 *
 * - Saves the current standard input for restoration later.
 * - Captures user input and appends it if valid.
 * - If canceled (CTRL+C) or an error occurs, frees memory and returns NULL.
 *
 * Return: The updated input string with appended input, or NULL on failure.
 */
char *process_trailing_pipe(t_shell *shell, char *line)
{
	char *additional_input;

	additional_input = NULL;
	signal(SIGINT, sig_handler_hd);
	shell->stdin_saved = dup(STDIN_FILENO);
	if (shell->stdin_saved == -1)
	{
		perror("Failed to save STDIN");
		return (NULL);
	}
	while (1)
	{
		additional_input = readline("> ");
		if (!additional_input || g_sig == SIGINT)
		{
			g_sig = 0;
			shell->exit_stat = restore_and_cleanup(shell, -1, 1);
			free(line);
			return (NULL);
		}
		if (!is_input_empty(additional_input))
			return (concat_and_cleanup(shell, line, additional_input));
		free(additional_input);
	}
	return (finalize_pipe_processing(shell, line));
}

/**
 * concat_and_cleanup - Concatenates two strings and frees original inputs.
 *
 * @shell: Shell structure managing shell state.
 * @line: Original input string.
 * @additional_input: Newly captured input string.
 *
 * This function joins `line` and `additional_input`,
 * then frees both input strings. If allocation fails,
 * it ensures proper cleanup of shell resources.
 *
 * Return: The concatenated string, or NULL on failure.
 */
static char *concat_and_cleanup(t_shell *shell, char *line, char *additional_input)
{
	char *updated_input;

	updated_input = ft_strjoin(line, additional_input);
	free(additional_input);
	if (!updated_input)
	{
		shell->exit_stat = restore_and_cleanup(shell, 0, 1);
		free(line);
		return (NULL);
	}
	shell->exit_stat = restore_and_cleanup(shell, 0, 0);
	free(line);
	return (updated_input);
}

/**
 * finalize_pipe_processing - Restores input state and finalizes handling.
 *
 * @shell: Shell structure managing shell state.
 * @line: Processed input string to be returned.
 *
 * Restores the original standard input and ensures proper cleanup.
 * Closes any saved file descriptors and resets shell state.
 *
 * Return: The processed input string, or NULL on failure.
 */
static char *finalize_pipe_processing(t_shell *shell, char *line)
{
	if (restore_and_cleanup(shell, 0, 0) != 0)
	{
		free(line);
		return (NULL);
	}
	if (shell->stdin_saved != -1)
	{
		close(shell->stdin_saved);
		shell->stdin_saved = -1;
	}
	return (line);
}
