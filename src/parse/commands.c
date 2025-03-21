/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:00:53 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/21 13:52:17 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * initialize_command - Initializes the fields of a command structure.
 *
 * @cmd: Pointer to the command structure to initialize.
 *
 * Sets all fields of the command structure to their initial values:
 * `NULL` for pointers, `0` for integers, and `-1` for file descriptors.
 * This ensures a clean state before populating the structure.
 */
void initialize_command(t_cmd *cmd)
{
    cmd->cmd_name = NULL;           // Initialize the command name as NULL
    cmd->cmd_path = NULL;           // Initialize the command path as NULL
    cmd->cmd_index = 0;             // Initialize the command index to 0
    cmd->cmd_args = NULL;           // Initialize the command arguments as NULL
    cmd->cmd_arg_count = 0;         // Initialize the argument count to 0
    cmd->redir_start = NULL;        // Initialize the first redirection as NULL
    cmd->redir_end = NULL;          // Initialize the last redirection as NULL
    cmd->input_fd = -1;             // Initialize the input file descriptor to -1 (no redirection)
    cmd->output_fd = -1;            // Initialize the output file descriptor to -1 (no redirection)
    cmd->cmd_exit_status = 0;       // Initialize the exit status to 0
}

int count_pipes(char *line)
{
	int i;
	int pipe_count;

	i = 0;
	pipe_count = 0;
	while (line[i])
	{
		if (line[i] == '|' && !check_quotes(line, i))
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

/**
 * allocate_command_structs - Allocates and initializes command structures.
 *
 * @msh: Pointer to the shell structure containing the command array.
 * @cmd_count: The total number of commands to allocate.
 *
 * Iterates through the `msh->cmds` array, allocating memory for each
 * command structure and initializing it using `initialize_command`.
 * If allocation fails, frees previously allocated memory and returns 1.
 *
 * Returns: 0 on success, or 1 on allocation failure.
 */
static int allocate_command_structs(t_msh *msh, int cmd_count)
{
    int i;
    i = 0;
    while (i < cmd_count)
    {
        msh->cmds[i] = malloc(sizeof(t_cmd));
        if (!msh->cmds[i])
        {
            ft_putendl_fd("Failed to allocate memory for struct", 2);
            clean_cmds(msh->cmds);  // Assuming `clean_cmds` frees memory properly
            return (1);
        }
        initialize_command(msh->cmds[i]);
        i++;
    }
    msh->cmds[cmd_count] = NULL;
    return (0);
}

/**
 * build_command_structs - Prepares the array of command structures.
 *
 * @msh: Pointer to the shell structure containing the command details.
 * @input: The input line to process.
 *
 * Calculates the number of commands based on the pipe count in the input
 * line and allocates memory for the command array. Calls `allocate_command_structs`
 * to allocate and initialize individual command structures.
 *
 * Returns: 0 on success, or 1 if memory allocation fails.
 */
int build_command_structs(t_msh *msh, char *input)
{
    int command_count;

    command_count = count_pipes(input) + 1;
    msh->cmd_count = command_count;
    msh->cmds = ft_calloc(command_count, sizeof(t_cmd));
    if (!msh->cmds)
    {
        ft_putendl_fd("Failed to allocate memory for command array", 2);
        return (1);
    }
    if (allocate_command_structs(msh, command_count))
        return (1);
    return (0);
}




