/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:43:11 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/23 16:58:40 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_string_while(t_msh *msh, t_cmd *cmd, int i, int *cmd_found)
{
	int	prev_i;

	while (cmd->seg[i])
	{
		prev_i = i;

		if (is_redirection(cmd, i))      // handles <, >, etc.
			i = handle_redirections(msh, cmd, i);
		else if (*cmd_found == 0)        // no command yet? get it
			i = handle_cmd_name(cmd, i);
		else                             // after command: parse args
			i = handle_cmd_args(msh, cmd, i);

		if (i == -1)
			return (-1);

		/* if (i == prev_i)                 // 🔥 THIS IS THE PROBLEM
		{
			fprintf(stderr, "No progress in loop at index %d\n", i);
			return (-1);
		} */
	}
	return (i);
}


/**
 * parse_cmd_string - Parses a command segment by handling expansion and tokenizing.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the command structure to fill.
 *
 * This function:
 *   1. Expands variables and tokens (e.g., $HOME, quotes, etc.)
 *   2. Parses the segment string for redirections, command name, and arguments.
 *   3. Ensures at least one argument is created if only command is found.
 *
 * Return: 0 on success, 1 on failure.
 */
int	parse_cmd_string(t_msh *msh, t_cmd *cmd)
{
	int	i = 0;
	int	cmd_found = 0;

	if (handle_expand(msh, &cmd))
		return (1);

	i = cmd_string_while(msh, cmd, i, &cmd_found);
	if (i == -1)
		return (1);

	if (cmd_found && (!cmd->args || !cmd->args[0]))
	{
		if (no_args(cmd, i) == -1)
			return (1);
	}

	return (0);
}


/**
 * parse_line - Parses all command segments in the msh structure.
 *
 * @msh: Pointer to the shell structure which holds the command array.
 *
 * This is the top-level parser that loops through all command segments
 * (usually split by '|') and processes them one by one using `parse_cmd_string`.
 * On failure, it performs cleanup and returns an error.
 *
 * Return: 0 on success, 1 if any command segment fails to parse.
 */
int	parse_line(t_msh *msh)
{
	int	index = 0;

	while (msh->cmd[index])
	{
		msh->cmd[index]->cmd_index = index;

		if (parse_cmd_string(msh, msh->cmd[index]))
		{
			msh->exit_code = 1;
			unlink_all_heredocs(msh);
			clean_cmds(msh->cmd);  // frees memory
			msh->cmd = NULL;       // avoids double-free
			return (1);
		}

		index++;
	}

	return (0);
}
