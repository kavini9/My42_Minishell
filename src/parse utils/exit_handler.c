/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:57:33 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/23 16:19:21 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

/**
 * @brief Cleans up resources and exits the shell on failure.
 *
 * @param msh Pointer to the shell structure containing resources to free.
 * @param i Index of the current command being executed.
 * @param exit_status Exit status code to terminate the shell with.
 *
 * Performs a comprehensive cleanup: closes file descriptors, unlinks heredocs,
 * frees environment and command memory, closes pipes, and exits the shell.
 */
void	exit_for_failure(t_msh *msh, int i, int exit_status)
{
	close_all_pipes(msh);
	unlink_all_heredocs(msh);
	if (msh->cmds[i]->output_fd > 2)
		close(msh->cmds[i]->output_fd);
	if (msh->cmds[i]->input_fd > 2)
		close(msh->cmds[i]->input_fd);
	clean_env(msh->env, msh->pending);
	clean_cmds(msh->cmds);
	if (msh->cmd_count > 1)
		ft_free_int_arr_with_size(msh->pipes, msh->cmd_count - 1);
	free(msh->cmds);
	free(msh->cwd);
	free(msh->old_wd);
	ft_free_array(msh->envl);
	free(msh->prompt);
	free(msh);
	exit(exit_status);
}

/**
 * @brief Cleans up resources and exits the shell gracefully.
 *
 * @param msh Pointer to the shell structure.
 * @param i Index of the current command being executed.
 * @param exit_status Exit status code to terminate the shell with.
 *
 * Frees memory, closes valid file descriptors, pipes, and other
 * shell-level allocations before exiting cleanly.
 */
void	exit_for_success(t_msh *msh, int i, int exit_status)
{
	if (msh->cmds[i]->output_fd != STDOUT_FILENO && msh->cmds[i]->output_fd != -1)
		close(msh->cmds[i]->output_fd);
	if (msh->cmds[i]->input_fd != STDIN_FILENO && msh->cmds[i]->input_fd != -1)
		close(msh->cmds[i]->input_fd);
	clean_env(msh->env, msh->pending);
	clean_cmds(msh->cmds);
	if (msh->cmd_count > 1)
		ft_free_int_arr_with_size(msh->pipes, msh->cmd_count - 1);
	free(msh->cmds);
	free(msh->cwd);
	free(msh->old_wd);
	ft_free_array(msh->envl);
	free(msh->prompt);
	free(msh);
	exit(exit_status);
}

/**
 * @brief Frees command memory and unlinks heredoc files.
 *
 * @param msh Pointer to the shell structure containing commands and heredocs.
 *
 * This function is useful for intermediate command cleanup
 * (e.g., after parse failure).
 */
void	clean_cmd_unlink(t_msh *msh)
{
	unlink_all_heredocs(msh);
	clean_cmds(msh->cmds);
}

/**
 * @brief Frees heredoc-related dynamic memory.
 *
 * @param arg Pointer to the heredoc expansion context (t_expand).
 * @param expan The expanded heredoc string to free.
 */
void	hd_free(t_expand *arg, char *expan)
{
	free(arg->value);
	free(expan);
}

/**
 * @brief Closes all pipe file descriptors used for inter-process communication.
 *
 * @param msh Pointer to the shell structure containing pipes.
 */
void	close_all_pipes(t_msh *msh)
{
	int	j = 0;

	while (j < msh->cmd_count - 1)
	{
		if (msh->pipes && msh->pipes[j])
		{
			close(msh->pipes[j][0]);
			close(msh->pipes[j][1]);
		}
		j++;
	}
}
