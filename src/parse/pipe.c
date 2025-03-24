/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:36:04 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/24 13:30:28 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * validate_pipe_position - Ensures valid syntax for a specific pipe (`|`) operator.
 *
 * @line: Input command string.
 * @i: Current index of the pipe operator in the string.
 * @msh: Shell structure managing shell state and exit status.
 *
 * This function checks if a valid command follows a pipe (`|`). If another
 * pipe or an invalid token is found, an error message is printed.
 *
 * Return:
 * - 1 if the syntax is invalid.
 * - 0 if valid.
 */
static int	validate_pipe_position(char *line, int i, t_msh *msh)
{
	int	j;

	j = skip_whitespace(line, i + 1);
	if (line[j] == '|' && !check_quotes(line, j))
	{
		ft_putstr_fd("syntax error near unexpected token '|'", 2);
		msh->exit_code = 2;
		return (1);
	}
	return (0);
}

/**
 * detect_consecutive_pipes - Checks for consecutive pipes without valid tokens.
 *
 * @line: Input string to check.
 * @msh: Shell structure managing shell state and exit status.
 *
 * Iterates through the input string, ensuring that pipes are not used
 * consecutively without valid commands between them. Skips quoted characters
 * and whitespace to prevent false errors.
 *
 * Return:
 * - 1 if syntax errors are found.
 * - 0 otherwise.
 */
static int	detect_consecutive_pipes(char *line, t_msh *msh)
{
	int	i;
	int	pipe_found;

	i = 0;
	pipe_found = 0;
	while (line[i])
	{
		if (line[i] == '|' && !check_quotes(line, i))
		{
			if (validate_pipe_position(line, i, msh))
				return (1);
			pipe_found = 1;
		}
		else if (!ft_isspace(line[i])) // Reset if a valid token is found
			pipe_found = 0;
		i++;
	}
	return (0);
}

/**
 * handle_trailing_pipe - Manages cases where the input ends with a pipe (`|`).
 *
 * @msh: Shell structure managing shell state.
 * @line: Pointer to the input string (modifiable for appending more input).
 *
 * If the command ends with a pipe, the function prompts the user for more input.
 * It uses `get_trailing_input()` to retrieve additional input and appends it to
 * the existing command string. If no input is provided, an error is returned.
 *
 * Return:
 * - 1 if handling fails.
 * - 0 if input is successfully extended.
 */
static int	handle_trailing_pipe(t_msh *msh, char **line)
{
	int		i;
	char	*extended_line;

	i = ft_strlen(*line) - 1;
	while (i >= 0 && ft_isspace((*line)[i])) // Ignore trailing spaces
		i--;
	if (i >= 0 && (*line)[i] == '|' && !check_quotes(*line, i))
	{
		extended_line = get_trailing_input(msh, *line);
		if (!extended_line)
		{
			*line = NULL;
			return (1);
		}
		*line = extended_line;
	}
	return (0);
}

/**
 * validate_pipe - Validates the syntax of pipe characters ('|') in the input command.
 *
 * @line: Pointer to the command line input.
 * @msh: Pointer to the minishell structure storing shell state.
 * 
 * This function enforces Bash-like syntax rules for pipes:
 * - Detects if the command starts with a pipe (`|`), which is a syntax error.
 * - Detects consecutive pipes (`||` or `| |`), reporting a syntax error.
 * - Detects a trailing pipe (e.g., `ls |`), prompting for additional input.
 * - Ensures that pipes inside quotes are not treated as errors (quotes are ignored).
 *
 * If an invalid pipe usage is detected, an error message is printed, 
 * and the exit code is set to 2.
 *
 * Return:
 * - 1 if an invalid pipe usage is detected (syntax error).
 * - 0 if the pipe usage is valid.
 */
int	validate_pipe(char **line, t_msh *msh)
{
	int	i;
	int	j;

	i = skip_whitespace(*line, 0);

	// Check if the first non-space character is '|'
	if ((*line)[i] == '|' && !check_quotes(*line, i))
	{
		j = i;
		while ((*line)[j] == '|') // Capture multiple consecutive pipes
			j++;

		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, *line + i, j - i); // Print the exact token that caused the error
		ft_putendl_fd("'", 2);
		msh->exit_code = 2;
		return (1);
	}

	// Check for other invalid pipe usages: consecutive pipes or trailing pipe
	if (detect_consecutive_pipes(*line, msh) || handle_trailing_pipe(msh, line))
		return (1);

	return (0);
}

 