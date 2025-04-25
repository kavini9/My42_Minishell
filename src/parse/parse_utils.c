/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:25:54 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/24 21:06:53 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * no_args - Creates an argument array with only the command.
 *
 * @cmd: Pointer to the command structure.
 * @i: Current position in the command string.
 *
 * Allocates memory for an argument array containing the command as the sole
 * argument. Returns the current position in the string or -1 on failure.
 */
int	no_args(t_cmd *cmd, int i)
{
	cmd->args = ft_calloc(2, sizeof(char *));
	if (!cmd->args)
		return (-1);

	cmd->args[0] = ft_strdup(cmd->command);
	if (!cmd->args[0])
	{
		free(cmd->args);
		cmd->args = NULL;
		return (-1);
	}
	cmd->args[1] = NULL;
	cmd->a_num = 1;
	return (i);
}


/**
 * is_empty_command - Checks if a command segment is empty or invalid.
 *
 * @cmd: Pointer to the command structure.
 * @i: Current position in the command string.
 *
 * Skips leading whitespace and checks if the command is either:
 *   - empty
 *   - ends with a pipe
 *
 * Return: true if the command is empty or invalid, false otherwise.
 */
bool	is_empty_command(t_cmd *cmd, int i)
{
	int	len;

	if (!cmd || !cmd->seg)
		return (true);

	len = ft_strlen(cmd->seg);

	// Skip whitespace
	while (cmd->seg[i] && ft_isspace(cmd->seg[i]))
		i++;

	// If segment ends or only contains a pipe, it's invalid
	if (!cmd->seg[i] || cmd->seg[i] == '|')
		return (true);

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
/*
int	add_char(char *str, t_expand *arg)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
		//printf("_line: %d\n", __LINE__);
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
*/

int	add_char(char *str, t_expand *arg)
{
	char	*temp;
	int	len_arg_val;

	len_arg_val = ft_strlen(arg -> value);
	temp = malloc((len_arg_val + 2) * sizeof(char));
	if (!temp)
		return (1);
	ft_memcpy(temp, arg -> value, len_arg_val);
	temp[len_arg_val] = str[arg -> i];
	temp[len_arg_val + 1] = '\0';
	free(arg -> value);
	arg -> value = temp;
	arg -> i++;
	return (0);
}
//no need to strdup arg-> value imo. it is already malllocked and we can do like
/*
temp =   arg -> value;
arg -> value = ft_strjoin(temp3, str[arg -> i]);
free(temp);
*/