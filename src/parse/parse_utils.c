/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:25:54 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/16 08:45:34 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * no_args - Creates a minimal argument array containing only the command.
 *
 * @cmd: Pointer to the command structure.
 * @i: Current position in the command string.
 *
 * Allocates memory for a command array with the command as the only argument.
 * Returns the current index if successful, or -1 on allocation failure.
 */
int	no_args(t_cmd *cmd, int i)
{
	cmd->cmd = ft_calloc(2, sizeof(char *));
	if (!cmd->cmd)
		return (-1);
	cmd->cmd[0] = ft_strdup(cmd->command);
	if (!cmd->cmd[0])
	{
		free(cmd->cmd);
		return (-1);
	}
	cmd->cmd[1] = NULL;
	return (i);
}

/**
 * is_empty_command - Checks if a command segment is empty or invalid.
 *
 * @cmd: Pointer to the command structure.
 * @i: Current position in the command string.
 *
 * Skips over whitespace and checks if the command is empty or ends
 * in an invalid state (like a trailing pipe).
 * Returns true if invalid or empty, false otherwise.
 */
bool	is_empty_command(t_cmd *cmd, int i)
{
	int	len;

	len = ft_strlen(cmd->seg);
	while (cmd->seg[i] && ft_isspace(cmd->seg[i]))
		i++;
	if (i >= len || cmd->seg[i] == '|')
		return (true);
/* 			if (i != len - 1)
	{
		if (!cmd->seg[i] || cmd->seg[i] == '|')
			return (true);
	} */
	return (false);
}

/**
 * add_char - Appends a single character from input to the expandable value.
 *
 * @str: Input string to take the character from.
 * @arg: Pointer to the t_expand structure managing the string and position.
 *
 * Adds the character at `arg->i` to `arg->value`, reallocating memory as needed.
 * Advances `arg->i`. Returns 0 on success, 1 on failure.
 */
int	add_char(char *str, t_expand *arg)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp2 = ft_strndup(&str[arg->i], 1);
	if (!temp2)
		return (1);
	temp3 = ft_strdup(arg->value);
	if (!temp3)
	{
		free(temp2);
		return (1);
	}
	temp = ft_strjoin(temp3, temp2);
	free(temp2);
	free(temp3);
	if (!temp)
		return (1);
	free(arg->value);
	arg->value = temp;
	arg->i++;
	return (0);
}

