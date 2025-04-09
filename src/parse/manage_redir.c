/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:21:15 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 11:21:46 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * double_redirect - Handles double redirection operators (<< or >>).
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @i: Index in the command segment where the redirection starts.
 *
 * Dispatches heredoc or append redirection handler depending on operator.
 *
 * Return: Updated index if successful, -1 on failure.
 */
static int double_redirect(t_msh *msh, t_cmd *cmd, int i)
{
	if (cmd->seg[i] == '<' && cmd->seg[i + 1] == '<')
		i = handle_heredoc(msh, cmd, i);
	else if (cmd->seg[i] == '>' && cmd->seg[i + 1] == '>')
		i = handle_append(cmd, i);
	if (i == -1)
		return -1;
	return i;
}

/**
 * single_redirect - Handles single redirection operators (< or >).
 *
 * @cmd: Pointer to the command structure.
 * @i: Index in the command segment where the redirection starts.
 *
 * Redirects to the appropriate input/output handler function.
 *
 * Return: Updated index if successful, -1 on failure.
 */
static int single_redirect(t_cmd *cmd, int i)
{
	if (cmd->seg[i] == '<')
		i = handle_redirect_in(cmd, i);
	else if (cmd->seg[i] == '>')
		i = handle_redirect_out(cmd, i);
	if (i == -1)
		return -1;
	return i;
}

/**
 * handle_redirections - Parses and processes redirection operators
 *                        in the command segment.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @i: Index in the command segment to start processing.
 *
 * Iterates through the segment string of a command, identifying
 * redirection operators (<, >, <<, >>) and dispatching them to
 * corresponding handlers. Handles allocation of redirection list nodes
 * and ensures parsing continues correctly or returns error.
 *
 * Return: Updated index if successful, -1 on failure.
 */
int handle_redirections(t_msh *msh, t_cmd *cmd, int i)
{
	while (i < (int)ft_strlen(cmd->seg) && cmd->seg[i])
	{
		if (is_redirection(cmd, i))
		{
			if (redirll_head_tail(cmd))
				return -1;
			if ((i + 1 < (int)ft_strlen(cmd->seg))
				&& ((cmd->seg[i] == '<' && cmd->seg[i + 1] == '<')
				|| (cmd->seg[i] == '>' && cmd->seg[i + 1] == '>')))
			{
				i = double_redirect(msh, cmd, i);
				if (i == -1)
					return -1;
			}
			else
			{
				i = single_redirect(cmd, i);
				if (i == -1)
					return -1;
			}
		}
		else
			break;
	}
	return i;
}




