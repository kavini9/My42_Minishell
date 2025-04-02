/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:43:11 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/31 18:35:01 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * no_args - Initializes the args array when no arguments are found.
 *
 * @cmd: Pointer to the command structure representing a single command segment.
 * @i: Current parsing index (returned unchanged).
 *
 * Allocates memory for the args array with the command as the only argument:
 *   - args[0] = strdup(command)
 *   - args[1] = NULL
 * Sets the argument count to 1.
 *
 * Return: The same index `i` on success, or -1 on allocation failure.
 */
int no_args(t_cmd *cmd, int i)
{
	cmd->args = ft_calloc(2, sizeof(char *));
	if (!cmd->args)
		return (-1);
	cmd->args[0] = ft_strdup(cmd->command);
	if (!cmd->args[0])
	{
		free(cmd->args);
		cmd->args = NULL;
		return (-1);
	}
	cmd->args[1] = NULL;
	cmd->arg_count = 1;
	return (i);
}

/**
 * cmd_string_while - Parses and processes elements in a command string.
 *
 * @msh: Pointer to the shell structure.
 * @token: Pointer to the command structure being parsed.
 * @i: Current index in the command string.
 * @cmd_found: Pointer to an integer that tracks if a command name has been found.
 *
 * Iterates over a command segment string to handle redirections, the command
 * name, and its arguments. Skips whitespace and updates `cmd_found` when a
 * valid command name is identified.
 *
 * Return: Updated index `i` on success, or -1 on failure.
 */
int cmd_string_while(t_msh *msh, t_cmd *token, int i, int *cmd_found)
{
	while (token->seg[i])
	{
		if (is_redirection(token, i))
		{
			i = handle_redirections(msh, token, i);
			if (i == -1)
				return (-1);
			i = skip_whitespace(token->seg, i);
		}
		else if (*cmd_found == 0)
		{
			i = handle_cmd_name(token, i);
			if (i == -1)
				return (-1);
			*cmd_found = 1;
		}
		else
		{
			i = handle_cmd_args(msh, token, i);
			if (i == -1)
				return (-1);
		}
	}
	return (i);
}

/**
 * parse_cmd_string - Parses a single command string and handles expansion.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the command structure for the command being parsed.
 *
 * This function handles variable expansion and delegates parsing logic to
 * `cmd_string_while`. If a command was found but no arguments were parsed,
 * `no_args` is called to set up the default args array.
 *
 * Return: 0 on success, or 1 on failure.
 */
int parse_cmd_string(t_msh *msh, t_cmd *cmd)
{
	int i;
	int cmd_found;

	i = 0;
	cmd_found = 0;
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
 * parse_line - Parses each command segment and stores parsed results.
 *
 * @msh: Pointer to the shell structure containing command tokens and execution data.
 *
 * Iterates through each command segment stored in `msh->tokens`, assigns a unique
 * index, and processes it with `parse_cmd_string`. Cleans up on failure.
 *
 * Return: 0 on success, or 1 on failure of any segment parsing.
 */
int parse_line(t_msh *msh)
{
	int index;

	index = 0;
	while (msh->tokens[index])
	{
		msh->tokens[index]->cmd_index = index;
		if (parse_cmd_string(msh, msh->tokens[index]))
		{
			msh->exit_code = 1;
			unlink_all_heredocs(msh);
			clean_tokens(msh->tokens);
			return (1);
		}
		index++;
	}
	return (0);
}
