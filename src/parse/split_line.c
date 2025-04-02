/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:56 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/02 15:49:08 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * trim_whitespace - Removes leading and trailing whitespace from a string.
 *
 * @seg: The input string to trim.
 *
 * Identifies the first and last non-whitespace characters in the string,
 * then shifts the trimmed portion to the beginning and null-terminates it.
 *
 * Return: Pointer to the trimmed string, or NULL if input is NULL.
 */
char	*trim_whitespace(char *seg)
{
	int	start;
	int	end;

	if (!seg)
		return (NULL);
	start = 0;
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
 * @cmd: Pointer to the t_cmd structure where the segment will be stored.
 * @line: Full input command line.
 * @start: Start index of the segment in the input line.
 * @end: End index (non-inclusive) of the segment in the input line.
 *
 * Copies the substring, trims whitespace, and assigns it to cmd->seg.
 *
 * Return: 0 on success, 1 on memory allocation failure or missing segment.
 */
static int	segment_handler(t_cmd *cmd, char *line, int start, int end)
{
	char	*trimmed;

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
 * split_line - Splits the input into command segments at unquoted pipes ('|').
 *
 * @line: The full input command line from the user.
 * @msh: Pointer to the shell structure containing the command linked list.
 *
 * Walks through the input, identifying unquoted pipes and passing each
 * command segment to segment_handler. The trimmed result is stored in
 * each t_cmd node's `seg` field.
 *
 * Return: 0 if successful, 1 on failure.
 */
int	split_line_by_pipe(char *line, t_msh *msh)
{
	int		i;
	int		start;
	int		index;
	t_cmd	*current;

	i = 0;
	start = 0;
	index = 0;
	current = msh->cmds;

	while (line[i])
	{
		if (line[i] == '|' && !check_quotes(line, i))
		{
			if (!current || segment_handler(current, line, start, i))
				return (1);
			current = current->next;
			start = i + 1;
		}
		i++;
	}
	if (!current || segment_handler(current, line, start, i))
		return (1);
	return (0);
}
