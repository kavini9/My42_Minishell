/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:36:04 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/14 19:01:36 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * validate_pipe_position - Ensures valid syntax for a specific pipe (`|`) operator.
 *
 * @line: Input command string.
 * @i: Current index of the pipe operator in the string.
 * @shell: Shell structure managing shell state and exit status.
 *
 * This function skips whitespace after the pipe and verifies that a valid
 * command follows. If another pipe or an invalid token is found, it prints
 * an error message.
 *
 * Return:
 * - 1 if the syntax is invalid.
 * - 0 if valid.
 */
static int	validate_pipe_position(char *line, int i, t_shell *shell)
{
	int	j;

	j = i + 1;
	j = skip_whitespace(line, j);
	if (line[j] == '|' && !check_quotes(line, j))
	{
		ft_putstr_fd("syntax error near unexpected token '|'", 2);
		shell->exit_stat = 2;
		return (1);
	}
	return (0);
}

/**
 * detect_consecutive_pipes - Checks for consecutive pipes without valid tokens.
 *
 * @line: Input string to check.
 * @shell: Shell structure managing shell state and exit status.
 *
 * Iterates through the input string, ensuring that pipes are not used
 * consecutively without valid tokens between them. Skips quoted characters
 * and whitespace.
 *
 * Return:
 * - 1 if syntax errors are found.
 * - 0 otherwise.
 */
static int	detect_consecutive_pipes(char *line, t_shell *shell)
{
	int	i;
	int	pipe_found;

	i = 0;
	pipe_found = 0;
	while (line[i])
	{
		if (line[i] == '|' && !check_quotes(line, i))
		{
			if (validate_pipe_position(line, i, shell))
				return (1);
			pipe_found = 1;
		}
		else if (ft_isspace(line[i]))
			pipe_found = 0;
		i++;
	}
	return (0);
}

/**
 * handle_trailing_pipe - Manages cases where the input ends with a pipe (`|`).
 *
 * @shell: Shell structure managing shell state.
 * @line: Pointer to the input string (modifiable to include more input).
 *
 * If the command ends with a pipe, prompts the user for additional input.
 * Uses `get_trailing_input()` to retrieve further input and appends it to the
 * existing command string. If no additional input is provided, it returns an error.
 *
 * Return:
 * - 1 if handling fails.
 * - 0 if the input is successfully extended.
 */
static int	handle_trailing_pipe(t_shell *shell, char **line)
{
	int		i;
	char	*extended_line;

	i = ft_strlen(*line) - 1;
	while (i >= 0 && ft_isspace((*line)[i]))
		i--;
	if (i >= 0 && (*line)[i] == '|' && !check_quotes(*line, i))
	{
		extended_line = get_trailing_input(shell, *line);
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
 * validate_pipe_syntax - Ensures proper syntax for pipes (`|`) in the input string.
 *
 * @line: Pointer to the input command string (modifiable for trailing pipes).
 * @shell: Shell structure managing shell state and exit status.
 *
 * This function checks if:
 * - The input starts with a pipe (invalid)
 * - There are consecutive pipes without valid tokens between them
 * - The input ends with a pipe (handled separately)
 *
 * Return:
 * - 1 if pipe syntax is invalid.
 * - 0 if syntax is valid.
 */
int	validate_pipe (char **line, t_shell *shell)
{
	int	i;

	i = 0;
	i = skip_whitespace(*line, i);
	if ((*line)[i] == '|' && !check_quotes(*line, i))
	{
		ft_putendl_fd("syntax error near unexpected token '|'", 2);
		shell->exit_stat = 2;
		return (1);
	}
	if (detect_consecutive_pipes(*line, shell))
		return (1);
	if (process_trailing_pipe(shell, line))
		return (1);
	return (0);
}




