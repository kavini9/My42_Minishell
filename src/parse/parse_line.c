/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:43:11 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 15:26:31 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * cmd_string_while - Parses tokens inside a command segment string.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the current command structure being parsed.
 * @i: Index for scanning the segment string.
 * @cmd_found: Pointer to a flag indicating if a command name has been found.
 *
 * Handles redirections, command name, and arguments. Skips whitespace,
 * and updates state as parsing progresses.
 *
 * Return: Updated index `i` on success, or -1 on failure.
 */
int	cmd_string_while(t_msh *msh, t_cmd *cmd, int i, int *cmd_found)
{
	while (cmd->seg[i])
	{
		if (is_redirection(cmd, i))
		{
			i = handle_redirections(msh, cmd, i);
			if (i == -1)
				return (-1);
			i = skip_whitespace(cmd->seg, i);
		}
		else if (*cmd_found == 0)
		{
			i = handle_cmd_name(cmd, i);
			if (i == -1)
				return (-1);
			*cmd_found = 1;
		}
		else
		{
			i = handle_cmd_args(msh, cmd, i);
			if (i == -1)
				return (-1);
		}
	}
	return (i);
}

/**
 * parse_cmd_string - Parses a command segment and expands variables.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the current command structure being parsed.
 *
 * Performs expansion and parses the segment for redirections,
 * command name, and arguments. If only the command is found with
 * no args, `no_args` initializes the args array.
 *
 * Return: 0 on success, or 1 on failure.
 */
int	parse_cmd_string(t_msh *msh, t_cmd *cmd)
{
	int	i;
	int	cmd_found;

	i = 0;
	cmd_found = 0;
	if (handle_expand(msh, &cmd))
		return (1);
	i = cmd_string_while(msh, cmd, i, &cmd_found);
	if (i == -1)
		return (1);
/* 	if (cmd_found && (!cmd->args || !cmd->args[0]))
	{
		if (no_args(cmd, i) == -1)
			return (1);
	} */
	return (0);
}

/**
 * parse_line - Parses all command segments in the linked list.
 *
 * @msh: Pointer to the shell structure containing the command list.
 *
 * Iterates through each t_cmd node, assigns an index, and processes it
 * using `parse_cmd_string`. Handles cleanup on failure.
 *
 * Return: 0 on success, 1 on failure.
 */
int	parse_line(t_msh *msh)
{
	t_cmd	*current;
	int		index;

	current = msh->cmds;
	index = 0;
	while (current)
	{
		current->cmd_index = index;
		if (parse_cmd_string(msh, current))
		{
			msh->exit_code = 1;
			unlink_all_heredocs(msh);
			clean_cmds(msh->cmds);
			return (1);
		}
		current = current->next;
		index++;
	}
	return (0);
}
