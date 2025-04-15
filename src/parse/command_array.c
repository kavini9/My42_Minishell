/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:00:53 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 17:23:50 by aoshinth         ###   ########.fr       */
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
	int	i;
	int	pipe_count;

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
 * initialize_command_struct - Initializes a single t_cmd structure.
 *
 * @cmd: Pointer to the command structure to initialize.
 *
 * Sets default values for each field to ensure a clean state.
 */
void	initialize_command_struct(t_cmd *cmd)
{
	cmd->seg = NULL;
	cmd->command = NULL;
	//cmd->command_path = NULL;
	cmd->cmd_index = 0;
	//cmd->args = NULL;
	//cmd->arg_count = 0;
	cmd->redir_start = NULL;
	cmd->redir_end = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->cmd_exit_status = 0;
	cmd->next = NULL;
}

/**
 * cmd_struct_while - Creates and initializes a linked list of t_cmd nodes.
 *
 * @msh: Pointer to the shell structure holding the command list.
 * @cmd_count: Number of command nodes to allocate.
 *
 * Returns: 0 on success, 1 if memory allocation fails.
 */
static int	cmd_struct_while(t_msh *msh, int cmd_count)
{
	t_cmd	*prev;
	t_cmd	*current;
	int		i;

	i = 0;
	prev = NULL;
	while (i < cmd_count)
	{
		current = malloc(sizeof(t_cmd));
		if (!current)
		{
			ft_putendl_fd("Failed to allocate memory for command struct", 2);
			free_cmd_list(msh->cmds);
			return (1);
		}
		initialize_command_struct(current);
		current->cmd_index = i;
		if (!prev)
			msh->cmds = current;
		else
			prev->next = current;
		prev = current;
		i++;
	}
	return (0);
}

/**
 * build_command_structs - Prepares the linked list of command structures.
 *
 * @msh: Pointer to the shell structure containing command info.
 * @line: The input line to parse.
 *
 * Determines number of commands from unquoted pipe characters
 * and initializes a linked list of command structures.
 *
 * Returns: 0 on success, 1 on failure.
 */
int	build_command_structs(t_msh *msh, char *line)
{
	int	cmd_count;

	cmd_count = count_pipes(line) + 1;
	msh->cmd_count = cmd_count;
	msh->cmds = NULL;
	if (cmd_struct_while(msh, cmd_count))
		return (1);
	return (0);
}


