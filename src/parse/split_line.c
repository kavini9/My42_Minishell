/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:56 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/31 18:38:40 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * trim_whitespace - Removes leading and trailing whitespace from a string.
 *
 * @seg: The input string to trim.
 *
 * Modifies the input string in-place by identifying the first and last
 * non-whitespace characters. Shifts the trimmed portion to the beginning
 * of the string and null-terminates it.
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
 * segment_handler - Extracts and stores a trimmed command segment.
 *
 * @cmd: Pointer to the command structure to store the trimmed segment.
 * @line: Full input line containing all segments.
 * @start: Start index of the current segment.
 * @end: End index (non-inclusive) of the current segment.
 *
 * Creates a substring of the current segment, trims whitespace, and stores
 * it in the command's `seg` field.
 *
 * Return: 0 on success, 1 on allocation failure or missing segment.
 */
static int segment_handler(t_cmd *cmd, char *line, int start, int end)
{
	char *trimmed;

	trimmed = ft_strndup(line + start, end - start);
	if (!trimmed)
		return (ft_putendl_fd("Allocation failed", 2), 1);
	trimmed = trim_whitespace(trimmed);
	cmd->seg = trimmed;
	if (!cmd->seg)
	{
		ft_putendl_fd("Missing command segment", 2);
		free(trimmed);
		return (1);
	}
	return (0);
}

/**
 * split_line - Splits the input line into command segments using unquoted pipes ('|').
 *
 * @line: The full input command line from the user.
 * @msh: Pointer to the shell structure containing the array of command structures.
 *
 * Iterates through the input line and splits it into segments at unquoted
 * pipe characters. Each segment is passed to `segment_handler` for trimming
 * and storing in the corresponding command structure.
 *
 * Return: 0 on successful parsing of all segments, 1 on error.
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

