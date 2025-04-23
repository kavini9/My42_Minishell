/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:30 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/22 22:41:33 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * handle_unmatched_quotes - Allows multiline input if quotes are unmatched.
 *
 * @line: Double pointer to the input line string to allow modification.
 *
 * If the input line has unmatched quotes, this function keeps prompting
 * the user (with `readline(">")`) for more input until all quotes are closed.
 * It reallocates and updates the line accordingly by appending new lines.
 *
 * Return: Always returns 0 (graceful exit on Ctrl+D is not an error).
 */
int	handle_unmatched_quotes(char **line)
{
	char	*extra_line;
	char	*temp;

	while (check_quotes(*line, ft_strlen(*line)))
	{
		extra_line = readline(">");
		if (!extra_line)
			return (0);//what should happen after this?
		temp = *line;
		*line = ft_strjoin(*line, "\n");
		free(temp);
		temp = *line;
		*line = ft_strjoin(*line, extra_line);
		free(temp);
		free(extra_line);
	}
	return (0);
}

/**
 * validate_input - Validates shell input for syntax errors and unmatched quotes.
 *
 * @line: Double pointer to the input string (modifiable).
 * @msh: Pointer to the shell structure to update exit code if needed.
 *
 * This function performs the following checks:
 * - Ensures all quotes are matched (supports multiline input)
 * - Validates pipe positions and usage
 * - Rejects unescaped semicolons or backslashes outside quotes
 * - Verifies correctness of redirection syntax
 *
 * Return: 1 on syntax error, 0 if input is valid.
 */
int	msh_validate_line(t_msh *msh, char **line) // changed name to go with msh
{
	int	i;

	handle_unmatched_quotes(line);
	if (validate_pipe(*line, msh))
		return (1);
	i = 0;
	while ((*line)[i])
	{
		if (!check_quotes(*line, i) && ((*line)[i] == ';' || (*line)[i] == '\\'))
		{
			ft_putendl_fd("invalid syntax", 2);
			msh->exit_code = 2;
			return (1);
		}
		i++;
	}
	return (check_redirects(*line, msh));
}