/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:54:41 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/24 16:09:54 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * cmd_string_while - Iterates through a command string and processes elements.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @i: Current position in the command string.
 * @cmd_found: Pointer to an integer indicating if a command has been found.
 *
 * Processes redirections, command names, and arguments in the command string.
 * Skips whitespace and updates `cmd_found` when a command is identified.
 * Returns the updated position in the string, or -1 on failure.
 */
int cmd_string_while(t_msh *msh, t_token *token, int i, int *cmd_found)
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
 * Handles variable expansion and iterates through the command string to
 * process redirections, command names, and arguments. Returns 1 on failure or
 * 0 on success.
 */
int parse_cmd_string(t_msh *msh, t_token *cmd)
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
    if (cmd_found && (!cmd->token_args || !cmd->token_args[0]))
        i = no_args(cmd, i);
    return (0);
}

/**
 * parse_line - Parses individual command segments into the shell structure.
 *
 * @msh: Pointer to the shell structure containing command and execution data.
 *
 * This function iterates through each command segment generated during input
 * splitting, assigns a unique index to each command, and parses the segment
 * into a command structure. If parsing fails for any command segment, the
 * function cleans up the resources, unlinks heredocs, and sets the shell's
 * exit status to an error state.
 *
 * Returns:
 * - 0 on successful parsing of all commands.
 * - 1 if parsing fails for any command segment.
 */
int parse_line(t_msh *msh)
{
    int index;

    index = 0;
    while (msh->tokens[index])  // Changed cmds to tokens
    {
        msh->tokens[index]->token_index = index;  // Changed cmds to tokens
        if (parse_cmd_string(msh, msh->tokens[index]))  // Changed cmds to tokens
        {
            msh->exit_code = 1;  // Changed exit_stat to exit_code
            unlink_all_heredocs(msh);
            clean_cmds(msh->tokens);  // Changed cmds to tokens
            return (1);
        }
        index++;
    }
    return (0);
}