/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:07:44 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 15:14:50 by aoshinth         ###   ########.fr       */
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
	if (msh->env)
		clean_env(msh->env, msh->envl);
	if (msh->cmds)
		clean_cmds(msh->cmds);
	if (msh->cmd_count > 1 && msh->pipes)
		ft_free_int_arr_with_size(msh->pipes, msh->cmd_count - 1);
	free(msh->cwd);
	free(msh->old_wd);
	free(msh->prompt);
}

/**
 * clean_cmds - Frees the command list and all associated data.
 *
 * @cmds: Pointer to the first t_cmd in the linked list.
 *
 * Frees each command's segments, arguments, redirections,
 * and the command nodes themselves.
 */
void	clean_cmds(t_cmd *cmds)
{
	t_cmd *tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free(cmds->seg);
		free(cmds->command);
		ft_free_array(cmds->cmd);
		if (cmds->redir_start)
			clean_redir(cmds->redir_start);
		free(cmds);
		cmds = tmp;
	}
}

/**
 * cleaner_for_success - Cleans up resources after
 * a successful pipeline execution.
 *
 * @msh: Pointer to the shell structure containing resources to clean.
 */
void	cleaner_for_success(t_msh *msh)
{
	clean_cmds(msh->cmds);
	if (msh->cmd_count > 1 && msh->pipes)
	{
		if (msh->pipes[msh->cmd_count - 2][0] > 0)
			close(msh->pipes[msh->cmd_count - 2][0]);
		if (msh->pipes[msh->cmd_count - 2][1] > 1)
			close(msh->pipes[msh->cmd_count - 2][1]);
	}
	if (msh->cmd_count > 1)
		ft_free_int_arr_with_size(msh->pipes, msh->cmd_count - 1);
}

/**
 * free_and_close_pipes - Frees and closes all pipe file descriptors
 *                        in the shell.
 *
 * @msh: Pointer to the shell structure containing the pipes to clean.
 *
 * Closes the read/write ends of each pipe and frees memory.
 */
void	free_and_close_pipes(t_msh *msh)
{
	int	i;

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
	clean_cmds(msh->cmds);
	if (msh->cmd_count > 1 && msh->pipes)
		free_and_close_pipes(msh);
}



/**
 * unlink_all_heredocs - Removes all temporary heredoc files from command list.
 *
 * @msh: Pointer to the main shell structure (t_msh).
 *
 * Iterates through each command’s redirection list and removes any
 * temporary files created for heredoc (<<) redirections.
 */
void unlink_all_heredocs(t_msh *msh)
{
	t_cmd *cmd = msh->cmds;
	t_redir *redir;

	while (cmd)
	{
		redir = (t_redir *)cmd->redir_start;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->heredoc_name)
			{
				unlink(redir->heredoc_name);
				free(redir->heredoc_name);
				redir->heredoc_name = NULL;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
