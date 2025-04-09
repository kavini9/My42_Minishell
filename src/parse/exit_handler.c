/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:57:33 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 15:09:38 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * exit_for_failure - Cleans up resources and exits the shell on failure.
 *
 * @msh: Pointer to the shell structure containing resources to free.
 * @i: Index of the current command being executed.
 * @exit_status: Exit status code to terminate the shell with.
 *
 * This function performs a comprehensive cleanup, including closing file
 * descriptors, unlinking heredocs, freeing memory, and releasing resources
 * before terminating the shell with the specified exit status.
 */
void	exit_for_failure(t_msh *msh, int i, int exit_status)
{
	close_all_pipes(msh);
	unlink_all_heredocs(msh);
	if (msh->cmds[i].output_fd > 2)
		close(msh->cmds[i].output_fd);
	if (msh->cmds[i].input_fd > 2)
		close(msh->cmds[i].input_fd);
	clean_env(msh->env , msh->pending);
	clean_cmds(msh->cmds);
	free(msh->cmds);
	free(msh->cwd);
	free(msh->old_wd);
	ft_free_array(msh->envl);
	free(msh->prompt);
	free(msh);
	exit(exit_status);
}

/**
 * exit_for_success - Cleans up resources
 * and exits the shell with the given status upon success.
 *
 * @msh: Pointer to the shell structure containing resources to free.
 * @i: Index of the current command being executed.
 * @exit_status: Exit status code to terminate the shell with.
 */
void	exit_for_success(t_msh *msh, int i, int exit_status)
{
	if (msh->cmds[i].output_fd != STDOUT_FILENO && msh->cmds[i].output_fd != -1)
		close(msh->cmds[i].output_fd);
	if (msh->cmds[i].input_fd != STDIN_FILENO && msh->cmds[i].input_fd != -1)
		close(msh->cmds[i].input_fd);
	clean_env(msh->env, msh->pending);
	clean_cmds(msh->cmds);
	free(msh->cmds);
	free(msh->cwd);
	free(msh->old_wd);
	ft_free_array(msh->envl);
	free(msh->prompt);
	free(msh);
	exit(exit_status);
}

/**
 * clean_cmd_unlink - Cleans up command resources and unlinks heredocs.
 *
 * @msh: Pointer to the shell structure containing commands and heredocs.
 */
void	clean_cmd_unlink(t_msh *msh)
{
	unlink_all_heredocs(msh);
	clean_cmds(msh->cmds);
}

/**
 * hd_free - Frees resources allocated during heredoc expansion.
 *
 * @arg: Pointer to the expansion structure containing the value to free.
 * @expan: Pointer to the expanded string to free.
 */
void	hd_free(t_expand *arg, char *expan)
{
	free(arg->value);
	free(expan);
}

/**
 * close_all_pipes - Closes all pipes used in the shell.
 *
 * @msh: Pointer to the shell structure containing the pipes to close.
 */
void	close_all_pipes(t_msh *msh)
{
	int	j;

	j = 0;
	while (j < msh->cmd_count - 1)
	{
		close(msh->pipes[j][0]);
		close(msh->pipes[j][1]);
		j++;
	}
}
