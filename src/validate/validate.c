/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:30 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/28 15:53:20 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /**
//  * handle_unmatched_quotes - Allows multiline input if quotes are unmatched.
//  *
//  * @line: Double pointer to the input line string to allow modification.
//  *
//  * If the input line has unmatched quotes, this function keeps prompting
//  * the user (with `readline(">")`) for more input until all quotes are closed.
//  * It reallocates and updates the line accordingly by appending new lines.
//  *
//  * Return: Always returns 0 (graceful exit on Ctrl+D is not an error).
//  */
// int	handle_unmatched_quotes(char **line)
// {
// 	char	*extra_line;
// 	char	*temp;

// 	while (check_quotes(*line, ft_strlen(*line)))
// 	{
// 		extra_line = readline(">");
// 		if (!extra_line)
// 			return (0);//what should happen after this?
// 		temp = *line;
// 		*line = ft_strjoin(*line, "\n");
// 		free(temp);
// 		temp = *line;
// 		*line = ft_strjoin(*line, extra_line);
// 		free(temp);
// 		free(extra_line);
// 	}
// 	return (0);
// }

// /**
//  * validate_input - Validates shell input for syntax errors and unmatched quotes.
//  *
//  * @line: Double pointer to the input string (modifiable).
//  * @msh: Pointer to the shell structure to update exit code if needed.
//  *
//  * This function performs the following checks:
//  * - Ensures all quotes are matched (supports multiline input)
//  * - Validates pipe positions and usage
//  * - Rejects unescaped semicolons or backslashes outside quotes
//  * - Verifies correctness of redirection syntax
//  *
//  * Return: 1 on syntax error, 0 if input is valid.
//  */
// int	msh_validate_line(t_msh *msh, char **line) // changed name to go with msh
// {
// 	int	i;

// 	handle_unmatched_quotes(line);
// 	if (validate_pipe(*line, msh))
// 		return (1);
// 	i = 0;
// 	while ((*line)[i])
// 	{
// 		if (!check_quotes(*line, i) && ((*line)[i] == ';' || (*line)[i] == '\\'))
// 		{
// 			ft_putendl_fd("invalid syntax", 2);
// 			msh->exit_code = 2;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (check_redirects(*line, msh));
// }


#include "../../includes/minishell.h"

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

static int	detect_consecutive_pipes(char *line, t_msh *msh)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && !check_quotes(line, i))
		{
			if (validate_pipe_position(line, i, msh))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	handle_trailing_pipe(t_msh *msh, char *line)
{
	int		i;
	char	*extended_line;

	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_isspace(line[i])) // Ignore trailing spaces
		i--;
	if (i >= 0 && line[i] == '|' && !check_quotes(line, i))
	{
		extended_line = get_trailing_input(msh, line);
		if (!extended_line)
		{
			line = NULL;
			return (1);
		}
		line = extended_line;
	}
	return (0);
}

int	validate_pipe(char *line, t_msh *msh)
{
	int	i;
	int	j;

	i = skip_whitespace(line, 0);

	// Check if the first non-space character is '|'
	if (line[i] == '|' && !check_quotes(line, i))
	{
		j = i;
		while (line[j] == '|') // Capture multiple consecutive pipes
			j++;

		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, line + i, j - i); // Print the exact token that caused the error
		ft_putendl_fd("'", 2);
		msh->exit_code = 2;
		return (1);
	}

	// Check for other invalid pipe usages: consecutive pipes or trailing pipe
	if (detect_consecutive_pipes(line, msh) || handle_trailing_pipe(msh, line))
		return (1);

	return (0);
}

int	msh_validate_line(t_msh *msh, char **line)
{
	int	i;

		if (!check_quotes(*line, i))
		{
			ft_putendl_fd("syntax error: unmatched quotes", 2);
			msh->exit_code = 2;
			return (1);
		}
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