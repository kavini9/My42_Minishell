/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:04:34 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 11:05:20 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * this_is_redirection - Checks if the current character is a syntax delimiter.
 *
 * @cmd: Pointer to the t_cmd structure (contains the segment).
 * @name: Pointer to the t_expand structure (tracks current index).
 *
 * Returns 1 if the character at the current index is a redirection ('<', '>')
 * or a pipe ('|'), or if it is whitespace. Returns 0 otherwise.
 */
static int	this_is_redirection(t_cmd *cmd, t_expand *name)
{
	if (ft_isspace(cmd->seg[name->i]) || cmd->seg[name->i] == '<'
		|| cmd->seg[name->i] == '>' || cmd->seg[name->i] == '|')
		return (1);
	else
		return (0);
}

/**
 * quoted_cmd - Parses a command name inside quotes and appends it to the value.
 *
 * @name: Pointer to the t_expand structure managing quote state and value buffer.
 * @seg: Input segment string to parse.
 *
 * This function handles both single and double quotes, tracking quote state,
 * and copying characters into name->value. It stops when quotes are closed
 * or when an unquoted whitespace is found.
 *
 * Returns the new index on success, or -1 on error.
 */
static int	quoted_cmd(t_expand *name, char *seg)
{
	what_quote(seg, name);
	while (seg[name->i])
	{
		if (ft_isspace(seg[name->i]) && !name->sgl && !name->dbl)
			break ;
		else if (!name->sgl && !name->dbl && (seg[name->i] == '\''
				|| seg[name->i] == '"'))
		{
			what_quote(seg, name);
		}
		else if ((name->sgl && seg[name->i] == '\'')
			|| (name->dbl && seg[name->i] == '"'))
		{
			what_quote(seg, name);
		}
		else if (add_char(seg, name))
			return (free(name->value), -1);
	}
	return (name->i);
}

/**
 * handle_cmd_name - Extracts and sets the command name from a segment.
 *
 * @cmd: Pointer to the t_cmd structure containing the segment (cmd->seg).
 * @i: Start index for parsing (usually 0).
 *
 * This function:
 * - Skips leading whitespace
 * - Parses until a redirection, pipe, or quote is encountered
 * - Handles quoted command names
 * - Appends characters to build the command name
 * - Sets cmd->command accordingly
 *
 * Returns the index where parsing ends, or 1 on error.
 */
int	handle_cmd_name(t_cmd *cmd, int i)
{
	t_expand	name;

	i = skip_whitespace(cmd->seg, i);
	the_arg(&name, i);
	while (cmd->seg[name.i])
	{
		if (this_is_redirection(cmd, &name))
			break ;
		if (cmd->seg[name.i] == '\'' || cmd->seg[name.i] == '"')
		{
			name.i = quoted_cmd(&name, cmd->seg);
			if (ft_strlen(name.value) == 0)
			{
				free(name.value);
				cmd->command = ft_strdup("''");
				return (name.i);
			}
			break ;
		}
		else if (add_char(cmd->seg, &name))
			return (free(cmd->seg), 1);
	}
	cmd->command = ft_strdup(name.value);
	free(name.value);
	return (name.i);
}



