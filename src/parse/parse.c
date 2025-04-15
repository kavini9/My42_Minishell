/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:53:36 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/15 13:45:42 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Handles unmatched quotes by allowing multiline input.
 * If the user presses Ctrl+D (EOF), it exits gracefully without an error.
 */
int	handle_unmatched_quotes(char *line)
{
	char	*extra_line;
	char	*temp;

	while (check_quotes(line, ft_strlen(line)))
	{
		extra_line = readline(">");
		if (!extra_line)
			return (0);
		temp = line;
		line = ft_strjoin(line, "\n");
		free(temp);
		temp = line;
		line = ft_strjoin(line, extra_line);
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
int	validate_input(char *line, t_msh *msh)
{
	int	i;

	handle_unmatched_quotes(line);
	if (validate_pipe(line, msh))
		return (1);
	i = 0;
	while (line[i])
	{
		if (!check_quotes(line, i) && (line[i] == ';' || line[i] == '\\'))
		{
			ft_putendl_fd("invalid syntax", 2);
			msh->exit_code = 2;
			return (1);
		}
		i++;
	}
	return (check_redirects(line, msh));
}

/**
 * validate_and_parse - Validates and processes user input for execution.
 * @line: Pointer to the user input string.
 * @msh: Pointer to the msh structure.
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
int	msh_parse(char *line, t_msh *msh)
{
	if (validate_input(line, msh))
		return (1);
	if (build_command_structs(msh, line))
		return (1);
	if (split_line_by_pipe (line, msh))
		return (1);
	if (parse_line (msh))
		return (1);
	return (0);
}
