/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:53:36 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/22 22:41:54 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * msh_parse - Master parsing function that validates and structures input.
 *
 * @line: The raw user input string (not modified directly).
 * @msh: Pointer to the main shell structure to store parsed output.
 *
 * This function runs the full parsing pipeline:
 * - Validates syntax and unmatched quotes
 * - Allocates space for command structures
 * - Splits input into segments using unquoted pipes
 * - Parses each segment into command, arguments, and redirections
 *
 * Return: 0 if parsing was successful, 1 on any failure.
 */
int	msh_parse(char *line, t_msh *msh)
{
	if (build_command_structs(msh, line))
		return (1);
	if (split_line_by_pipe(line, msh))
		return (1);
	if (parse_line(msh))
		return (1);
	return (0);
}

