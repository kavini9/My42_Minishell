/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:56 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/26 14:39:31 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

/**
 * trim_whitespace - Removes leading and trailing whitespace from a string.
 *
 * @seg: The input string to trim.
 *
 * This function modifies the input string in-place. It finds the first and last
 * non-whitespace characters, shifts the relevant portion to the start of the buffer,
 * null-terminates the result, and returns the trimmed string.
 *
 * Return: Pointer to the trimmed string, or NULL if input is NULL.
 */
char *trim_whitespace(char *seg)
{
	int start = 0;
	int end;

	if (!seg)
		return (NULL);
	end = ft_strlen(seg) - 1;
	while (seg[start] && ft_isspace(seg[start]))
		start++;
	while (end >= start && ft_isspace(seg[end]))
		end--;
	ft_memmove(seg, seg + start, end - start + 1);
	seg[end - start + 1] = '\0';
	return (seg);
}

/**
 * segment_handler - Processes and stores a command segment in a token.
 *
 * @token: Pointer to the token structure to store the segment.
 * @line: The original input line.
 * @start: Starting index of the segment.
 * @end: Ending index (non-inclusive) of the segment.
 *
 * Extracts a substring from `line`, trims whitespace, and stores it in the
 * token's `command` field. Returns 1 on memory allocation failure, 0 on success.
 */
static int segment_handler(t_token *token, char *line, int start, int end)
{
	char *trimmed;

	trimmed = ft_strndup(line + start, end - start);
	if (!trimmed)
		return (ft_putendl_fd("Allocation failed", 2), 1);
	trimmed = trim_whitespace(trimmed);
	token->command = trimmed;
	if (!token->command)
	{
		ft_putendl_fd("Missing command", 2);
		free(trimmed);
		return (1);
	}
	return (0);
}

/**
 * split_line - Splits the input line into segments using unquoted pipe ('|') characters.
 *
 * @line: The input command line.
 * @msh: Pointer to the minishell structure where tokens are stored.
 *
 * This function iterates through the input string, identifying segments separated
 * by unquoted pipes (`|`). It calls `segment_handler` to trim and assign each
 * segment to a token in the shell structure.
 *
 * Return: 0 on success, or 1 on memory allocation or processing failure.
 */
int split_line(char *line, t_msh *msh)
{
	int i = 0;
	int start = 0;
	int index = 0;

	while (line[i])
	{
		if (line[i] == '|' && !check_quotes(line, i))
		{
			if (segment_handler(msh->tokens[index++], line, start, i))
				return (1);
			start = i + 1;
		}
		i++;
	}
	return segment_handler(msh->tokens[index], line, start, i);
}


