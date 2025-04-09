/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:53:06 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 14:55:34 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_heredoc_expander - Initializes the heredoc expansion process.
 *
 * @arg: Pointer to the expansion state structure to be initialized.
 * @expan: Pointer to the expansion result string, which will be allocated.
 *
 * Initializes the expansion state
 * and allocates an empty string for the expansion result.
 * Returns 0 on success or 1 on failure.
 */
static int	init_heredoc_expander(t_expand *arg, char **expan)
{
	if (the_arg(arg, 0))
		return (1);
	*expan = ft_strdup("");
	if (!(*expan))
		return (1);
	return (0);
}

/**
 * finalize_hd_expand - Finalizes heredoc variable expansion.
 *
 * @arg: Pointer to the expansion state structure.
 * @expan: Pointer to the accumulated expansion result.
 * @line: Pointer to the original heredoc line, which will be replaced.
 *
 * Joins the expanded result with the accumulated value,
 * replaces the original line,
 * and frees memory used during the process.
 * Returns 0 on success or -1 on failure.
 */
static int	finalize_hd_expand(t_expand *arg, char *expan, char **line)
{
	char	*temp;

	temp = ft_strjoin(expan, arg->value);
	free(arg->value);
	free(expan);
	if (!temp)
		return (-1);
	free(*line);
	*line = temp;
	return (0);
}

/**
 * heredoc_expander - Expands variables in a heredoc line.
 *
 * @msh: Pointer to the shell structure containing environment variables.
 * @line: Pointer to the heredoc line to be expanded.
 *
 * Iterates through the line, expanding variables prefixed by `$`. Handles errors
 * during expansion and ensures proper memory management.
 * Updates `line` with the expanded result.
 * Returns 0 on success, 1 or -1 on failure.
 */
int	heredoc_expander(t_msh *msh, char **line)
{
	t_expand	arg;
	char		*expan;

	if (init_heredoc_expander(&arg, &expan))
		return (1);
	while ((*line)[arg.i])
	{
		if ((*line)[arg.i] == '$' && (*line)[arg.i + 1]
			&& ft_isalnum((*line)[arg.i + 1]))
		{
			if (we_have_dollar(msh, &arg, *line) == -1)
			{
				hd_free(&arg, expan);
				return (-1);
			}
		}
		else if (add_char(*line, &arg))
		{
			hd_free(&arg, expan);
			return (-1);
		}
	}
	if (finalize_hd_expand(&arg, expan, line))
		return (1);
	return (0);
}

/**
 * check_expand - Handles variable expansion in heredoc if enabled.
 *
 * @msh: Pointer to the shell structure containing environment variables.
 * @cmd: Pointer to the command structure.
 * @line: Pointer to the heredoc line to be processed.
 * @fd: File descriptor of the heredoc temporary file.
 *
 * Expands variables in the heredoc line if the redirection requires expansion.
 * Cleans up resources and closes the file descriptor on failure.
 * Returns 0 on success or 1 on failure.
 */
int	check_expand(t_msh *msh, t_cmd *cmd, char **line, int fd)
{
	if (cmd->redir_end && cmd->redir_end->expand)
	{
		if (heredoc_expander(msh, line))
		{
			free(*line);
			close(fd);
			return (1);
		}
	}
	return (0);
}



