/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:07:44 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/25 18:46:28 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * mini_cleaner - Frees all allocated resources within the t_msh structure.
 *
 * @msh: Pointer to the shell structure containing resources to clean.
 *
 * Frees the environment, environment array, command structures, and pipes.
 * Ensures no memory leaks when the shell exits.
 */
void	mini_cleaner(t_msh *msh)
{
	if (msh->envl)
		clean_env(msh->envl, msh->envl);
	if (msh->cmd)
		clean_cmds(msh->cmd);
	if (msh->cmd_count > 1 && msh->pipes)
		ft_free_int_arr_with_size(msh->pipes, msh->cmd_count - 1);
	free(msh->cwd);
	free(msh->old_wd);
	free(msh->prompt);
}

/**
 * clean_cmds - Frees the command array and all associated data.
 *
 * @cmds: Pointer to the array of t_cmd structures.
 *
 * Frees each command's segments, arguments, redirections,
 * and the command structs themselves.
 */
void	clean_cmds(t_cmd **cmd  )
{
	int	i;

	if (!cmd)
		return;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->seg)
			free(cmd[i]->seg);
		if (cmd[i]->command)
			free(cmd[i]->command);
		if (cmd[i]->cmd)
			ft_free_array(cmd[i]->cmd);
		if (cmd[i]->redir_start)
			clean_redir(cmd[i]->redir_start);

		free(cmd[i]);
		cmd[i] = NULL;  // Optional: clear after free
		i++;
	}
	free(cmd);
}


/**
 * cleaner_for_success - Cleans up resources after
 * a successful pipeline execution.
 *
 * @msh: Pointer to the shell structure containing resources to clean.
 */
void	cleaner_for_success(t_msh *msh)
{
	if (msh->cmd)
		clean_cmds(msh->cmd);
	if (msh->cmd_count > 1 && msh->pipes)
	{
		if (msh->pipes[msh->cmd_count - 2][0] > 0)
			close(msh->pipes[msh->cmd_count - 2][0]);
		if (msh->pipes[msh->cmd_count - 2][1] > 1)
			close(msh->pipes[msh->cmd_count - 2][1]);
		ft_free_int_arr_with_size(msh->pipes, msh->cmd_count - 1);
	}
}

/**
 * free_and_close_pipes - Frees and closes all pipe file descriptors.
 *
 * @msh: Pointer to the shell structure containing the pipes to clean.
 */
void	free_and_close_pipes(t_msh *msh)
{
	int	i;

	if (!msh->pipes)
		return;

	i = 0;
	while (i < msh->cmd_count - 1)
	{
		if (msh->pipes[i][0] > 0)
			close(msh->pipes[i][0]);
		if (msh->pipes[i][1] > 1)
			close(msh->pipes[i][1]);
		free(msh->pipes[i]);
		i++;
	}
	free(msh->pipes);
	msh->pipes = NULL;
}

/**
 * cleaner_for_failure - Cleans up resources after a failed pipeline execution.
 *
 * @msh: Pointer to the shell structure containing resources to clean.
 *
 * Unlinks all heredocs, frees commands, pipes, and memory associated with failure.
 */
void	cleaner_for_failure(t_msh *msh)
{
	unlink_all_heredocs(msh);
	if (msh->cmd)
		clean_cmds(msh->cmd);
	if (msh->cmd_count > 1 && msh->pipes)
		free_and_close_pipes(msh);
}

/**
 * unlink_all_heredocs - Removes all temporary heredoc files from commands.
 *
 * @msh: Pointer to the main msh structure.
 *
 * Iterates through each command’s redirection list and removes any
 * temporary files created for heredoc (<<) redirections.
 */
void	unlink_all_heredocs(t_msh *line)
{
	t_redir	*current;
	int		i;

	i = 0;
	while (i < line->cmd_count)
	{
		current = line->cmd[i]->redir_start;
		while (current)
		{
			if (current->type == HEREDOC)
			{
				if (current->heredoc_name)
				{
					unlink(current->heredoc_name);
					free(current->heredoc_name);
					current->heredoc_name = NULL;
				}
			}
			current = current->next;
		}
		i++;
	}
}
