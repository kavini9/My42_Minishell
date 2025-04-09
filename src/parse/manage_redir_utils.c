/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:54:18 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/07 17:28:26 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_redirection - Checks if current character is a redirection operator.
 *
 * @cmd: Pointer to the current command.
 * @i: Current index in the segment.
 *
 * Returns true if character is < or > and not inside quotes.
 */
bool is_redirection(t_cmd *cmd, int i)
{
	if ((cmd->seg[i] == '>' || cmd->seg[i] == '<')
		&& !check_quotes(cmd->seg, i))
		return true;
	return false;
}

/**
 * handle_redirect_in - Processes input redirection (<).
 *
 * @cmd: Pointer to the current command.
 * @i: Current index in the segment.
 *
 * Parses the filename and sets redir_end to REDIR_IN.
 * Returns new index or -1 on failure.
 */
int handle_redirect_in(t_cmd *cmd, int i)
{
	char *filename = NULL;
	i++;
	i = parse_filename(cmd, i, &filename);
	if (i == -1 || !filename)
		return -1;
	((t_redir *)cmd->redir_end)->file = filename;
	((t_redir *)cmd->redir_end)->type = REDIR_IN;
	return i;
}

/**
 * handle_redirect_out - Processes output redirection (>).
 *
 * @cmd: Pointer to the current command.
 * @i: Current index in the segment.
 *
 * Parses the filename and sets redir_end to REDIR_OUT.
 * Returns new index or -1 on failure.
 */
int handle_redirect_out(t_cmd *cmd, int i)
{
	char *filename = NULL;
	i++;
	i = parse_filename(cmd, i, &filename);
	if (i == -1 || !filename)
		return -1;
	((t_redir *)cmd->redir_end)->file = filename;
	((t_redir *)cmd->redir_end)->type = REDIR_OUT;
	return i;
}

/**
 * handle_heredoc - Processes heredoc redirection (<<).
 *
 * @msh: Pointer to shell data.
 * @cmd: Pointer to current command.
 * @i: Current index in the segment.
 *
 * Sets delimiter, expands heredoc, and creates temp file.
 * Returns updated index or -1 on failure.
 */
int handle_heredoc(t_msh *msh, t_cmd *cmd, int i)
{
	char *delim = NULL;
	i += 2;
	if (cmd->seg[i] == '\'' || cmd->seg[i] == '"')
		((t_redir *)cmd->redir_end)->expand = false;
	i = parse_filename(cmd, i, &delim);
	if (i == -1 || !delim)
		return -1;
	((t_redir *)cmd->redir_end)->delimiter = delim;
	((t_redir *)cmd->redir_end)->type = HEREDOC;
	if (generate_hd_file(cmd))
		return -1;
	if (open_and_write_to_heredoc(msh, cmd))
		return -1;
	return i;
}

/**
 * handle_append - Processes append redirection (>>).
 *
 * @cmd: Pointer to the current command.
 * @i: Current index in the segment.
 *
 * Parses the filename and sets redir_end to APPEND.
 * Returns new index or -1 on failure.
 */
int handle_append(t_cmd *cmd, int i)
{
	char *filename = NULL;
	i += 2;
	i = parse_filename(cmd, i, &filename);
	if (i == -1 || !filename)
		return -1;
	((t_redir *)cmd->redir_end)->file = filename;
	((t_redir *)cmd->redir_end)->type = APPEND;
	return i;
}