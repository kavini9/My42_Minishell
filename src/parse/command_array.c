/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:00:53 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/23 08:22:07 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * count_pipes - Counts the number of unquoted pipe characters in a line.
 *
 * @line: The input line to process.
 *
 * Returns: The number of unquoted pipe characters found in the line.
 */
int	count_pipes(char *line)
{
	int	i = 0;
	int	pipe_count = 0;

	while (line[i])
	{
		if (line[i] == '|' && !check_quotes(line, i))
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

/**
 * initialize_command_struct - Initializes a single t_cmd structure.
 *
 * @cmd: Pointer to the command structure to initialize.
 *
 * Sets default values for each field to ensure a clean state.
 */
void	initialize_command_struct(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->a_num = 0;
	cmd->command = NULL;
	cmd->cmd = NULL;
	cmd->cmd_index = 0;
	cmd->redir_start = NULL;
	cmd->redir_end = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->cmd_exit_status = 0;
	// cmd->next = NULL; // removed: not used in array-based version
}

/**
 * cmd_struct_while - Allocates and initializes each command node in the array.
 *
 * @msh: Pointer to the shell structure.
 * @cmd_count: Number of command nodes to allocate.
 *
 * Returns: 0 on success, 1 on allocation failure.
 */
static int	cmd_struct_while(t_msh *msh, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		msh->cmds[i] = malloc(sizeof(t_cmd));
		if (!msh->cmds[i])
		{
			ft_putendl_fd("Failed to allocate memory for command struct", 2);
			clean_cmds(msh->cmds);
			return (1);
		}
		initialize_command_struct(msh->cmds[i]);
		i++;
	}
	msh->cmds[cmd_count] = NULL; // null-terminate the array
	return (0);
}

/**
 * build_command_structs - Builds an array of initialized command structures.
 *
 * @msh: Pointer to the main shell structure.
 * @line: The input line from user.
 *
 * Allocates the array of t_cmd * and fills with allocated & initialized t_cmd.
 *
 * Returns: 0 on success, 1 on error.
 */
int	build_command_structs(t_msh *msh, char *line)
{
	int	cmd_count = count_pipes(line) + 1;

	msh->cmd_count = cmd_count;

	msh->cmds = ft_calloc(cmd_count + 1, sizeof(t_cmd *)); // +1 for NULL terminator
	if (!msh->cmds)
	{
		ft_putendl_fd("Failed to allocate memory for command pointer array", 2);
		return (1);
	}
	if (cmd_struct_while(msh, cmd_count))
		return (1);
	return (0);
}

