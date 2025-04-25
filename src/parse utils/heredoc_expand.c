/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:53:06 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/16 09:30:08 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/**
 * @brief Initializes the heredoc expansion state and result buffer.
 *
 * @param arg Pointer to the expansion state structure to initialize.
 * @param expan Pointer to the result string (to be allocated as empty string).
 * @return 0 on success, 1 on failure.
 *
 * This sets up the internal state (`t_expand`) and allocates memory
 * for building the result of a heredoc expansion.
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
 * @brief Finalizes the heredoc expansion result by joining it and replacing input.
 *
 * @param arg Pointer to the expansion state (includes accumulated value).
 * @param expan The intermediate expanded result string.
 * @param line Pointer to the original line string (will be replaced).
 * @return 0 on success, -1 on failure.
 *
 * Frees intermediate buffers, joins the final result into `line`,
 * and ensures memory safety.
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
 * @brief Expands environment variables (`$VAR`) within a heredoc line.
 *
 * @param msh Pointer to shell structure containing environment.
 * @param line Line to expand (in-place update).
 * @return 0 on success, 1 or -1 on failure.
 *
 * This iterates through the given heredoc `line`, performs expansion
 * on variables like `$USER`, and replaces `line` with the expanded result.
 */
int	heredoc_expander(t_msh *msh, char *line)
{
	t_expand	arg;
	char		*expan;

	if (init_heredoc_expander(&arg, &expan))
		return (1);
	while ((line)[arg.i])
	{
		if ((line)[arg.i] == '$' && (line)[arg.i + 1]
			&& ft_isalnum((line)[arg.i + 1]))
		{
			if (we_have_dollar(msh, &arg, line) == -1)
			{
				hd_free(&arg, expan);
				return (-1);
			}
		}
		else if (add_char(line, &arg))
		{
			hd_free(&arg, expan);
			return (-1);
		}
	}
	if (finalize_hd_expand(&arg, expan, &line))
		return (1);
	return (0);
}

/**
 * @brief Performs heredoc variable expansion if enabled for the command.
 *
 * @param msh Pointer to shell structure.
 * @param cmd Pointer to current command being processed.
 * @param line Pointer to heredoc input line (possibly modified).
 * @param fd File descriptor of the heredoc temporary file.
 * @return 0 on success, 1 on failure.
 *
 * If expansion is needed for the last redirection in `cmd`, expands variables
 * in `line`. On failure, cleans up the line and file descriptor.
 */
int	check_expand(t_msh *msh, t_cmd *cmd, char **line, int fd)
{
	if (cmd->redir_end && cmd->redir_end->expand)
	{
		if (heredoc_expander(msh, *line))
		{
			free(*line);
			close(fd);
			return (1);
		}
	}
	return (0);
}
