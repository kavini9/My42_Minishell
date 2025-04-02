/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:00:53 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/31 18:47:26 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * initialize_cmd - Initializes the fields of a t_cmd structure.
 *
 * @cmd: Pointer to the command structure to initialize.
 *
 * Sets all fields of the command structure to their default values:
 * `NULL` for pointers, `0` for integers, and `-1` for file descriptors.
 * This ensures a clean state before populating the structure during parsing.
 */
void initialize_cmd(t_cmd *cmd)
{
	cmd->seg = NULL;
	cmd->command = NULL;
	cmd->command_path = NULL;
	cmd->cmd_index = 0;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->redir_start = NULL;
	cmd->redir_end = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->cmd_exit_status = 0;
	cmd->next = NULL;
}

/**
 * count_pipes - Counts the number of unquoted pipe symbols in a command line.
 *
 * @line: The input command line.
 *
 * Iterates through the input line and counts occurrences of the '|' character,
 * ignoring those that appear inside quotes.
 *
 * Return: The number of pipe symbols found.
 */
int count_pipes(char *line)
{
	int i = 0;
	int pipe_count = 0;

	while (line[i])
	{
		if (line[i] == '|' && !check_quotes(line, i))
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

/**
 * allocate_cmd_structs - Allocates and initializes t_cmd structures.
 *
 * @msh: Pointer to the shell structure containing the commands array.
 * @cmd_count: The total number of command structures to allocate.
 *
 * Allocates memory for each command structure in `msh->commands` and
 * initializes them using `initialize_cmd`. Cleans up and returns 1
 * on failure, or 0 on success.
 *
 * Return: 0 on success, or 1 on allocation failure.
 */
static int allocate_cmd_structs(t_msh *msh, int cmd_count)
{
	int i = 0;

	while (i < cmd_count)
	{
		msh->commands[i] = malloc(sizeof(t_cmd));
		if (!msh->commands[i])
		{
			ft_putendl_fd("Failed to allocate memory for command struct", 2);
			clean_commands(msh->commands);  // Assumes proper freeing
			return (1);
		}
		initialize_cmd(msh->commands[i]);
		i++;
	}
	msh->commands[cmd_count] = NULL;
	return (0);
}

/**
 * build_cmd_structs - Prepares the command structures based on pipe count.
 *
 * @msh: Pointer to the shell structure.
 * @line: The input command line string.
 *
 * Calculates the number of commands in the line by counting pipes.
 * Allocates memory for the array of command structures, then allocates
 * and initializes each structure using `allocate_cmd_structs`.
 *
 * Return: 0 on success, or 1 if memory allocation fails.
 */
int build_cmd_structs(t_msh *msh, char *line)
{
	int cmd_count;

	cmd_count = count_pipes(line) + 1;
	msh->cmd_count = cmd_count;
	msh->commands = ft_calloc(cmd_count + 1, sizeof(t_cmd *));
	if (!msh->commands)
	{
		ft_putendl_fd("Failed to allocate memory for command array", 2);
		return (1);
	}
	if (allocate_cmd_structs(msh, cmd_count))
		return (1);
	return (0);
}

