/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:56:49 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/16 10:49:52 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * skip_quoted_segment - Skips over a quoted section of the command segment.
 *
 * @seg: The input command segment.
 * @i: Index at the opening quote character.
 *
 * Advances the index to the matching closing quote.
 * Returns the index just after the closing quote.
 */
static int	skip_quoted_segment(const char *seg, int i)
{
	char	quote;

	quote = seg[i];
	i++;
	while (seg[i] && seg[i] != quote)
		i++;
	if (seg[i] == quote)
		i++;
	return (i);
}

/**
 * count_if_redirection - Skips over redirection symbols and content.
 *
 * @cmd: Pointer to the command structure.
 * @i: Current index in the command segment.
 *
 * Advances index past redirection and any immediate characters.
 * Returns the updated index.
 */
int	count_if_redirection(t_cmd *cmd, int i)
{
	while (cmd->seg[i] && ft_isspace(cmd->seg[i]))
		i++;
	while (cmd->seg[i] && !ft_isspace(cmd->seg[i])
		&& is_redirection(cmd, i))
		i++;
	return (i);
}

/**
 * only_redirect - Checks if a redirection follows an assignment.
 *
 * @str: The input string.
 * @i: Starting index to check from.
 *
 * Returns 1 if the character after `=` is a redirection or pipe,
 * otherwise returns 0.
 */
int	only_redirect(char *str, int i)
{
	int	n;

	n = i;
	while (str[n] && str[n] != '=')
		n++;
	if (!str[n])
		return (0);
	n++;
	if (str[n])
		n++;
	if ((str[n] == '>' || str[n] == '<') || str[n] == '|')
		return (1);
	return (0);
}

/**
 * count_args - Counts the number of arguments in a command segment.
 *
 * @cmd: Pointer to the command structure.
 * @i: The starting index in the command segment.
 *
 * Iterates through the command segment, counting arguments,
 * skipping over redirections and quoted segments.
 * Returns the number of arguments found.
 */
int	count_args(t_cmd *cmd, int i)
{
	int	args_count;

	args_count = 0;
	while (cmd->seg[i] && ft_isspace(cmd->seg[i]))
		i++;
	while (cmd->seg[i])
	{
		if (is_redirection(cmd, i))
			i = count_if_redirection(cmd, ++i);
		else
		{
			args_count++;
			while (cmd->seg[i] && (!ft_isspace(cmd->seg[i])
					|| check_quotes(cmd->seg, i)) && !is_redirection(cmd, i))
			{
				if (cmd->seg[i] == '\'' || cmd->seg[i] == '"')
					i = skip_quoted_segment(cmd->seg, i);
				else
					i++;
			}
		}
		while (cmd->seg[i] && ft_isspace(cmd->seg[i]))
			i++;
	}
	return (args_count);
}

/**
 * init_args_array - Allocates and initializes the command's argument array.
 *
 * @cmd: Pointer to the command structure.
 * @i: Index to start parsing for argument count.
 *
 * This function:
 *   - Uses count_args() to count how many arguments the segment contains.
 *   - Allocates memory for (arg_count + 1) arguments (including the command itself).
 *   - Sets cmd->cmd[0] to the command name (copied via ft_strdup).
 *   - Ensures the array is NULL-terminated.
 *
 * Returns:
 *   0  on success,
 *  -1 if allocation or duplication fails.
 */
int	init_args_array(t_cmd *cmd, int i)
{
	int	arg_count;

	arg_count = count_args(cmd, i);

	// +2: one for cmd[0] (command name), one for final NULL
	cmd->cmd = ft_calloc(arg_count + 2, sizeof(char *));
	if (!cmd->cmd)
		return (-1);

	cmd->cmd[0] = ft_strdup(cmd->command);
	if (!cmd->cmd[0])
	{
		ft_free_array(cmd->cmd);
		return (-1);
	}
	cmd->cmd_index = 0; // optional, if you use this to track filling
	return (0);
}

