/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:25:54 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/28 14:26:55 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * no_args - Sets args array with only the command when no arguments are found.
 *
 * @token: Pointer to the token structure representing a command segment.
 * @i: The current parsing index (returned unchanged).
 *
 * This function is used when a command (like "ls") has no additional arguments.
 * It allocates a minimal args array as follows:
 *   - args[0] = strdup(command)
 *   - args[1] = NULL
 *
 * Return: The same index `i` on success, or -1 on allocation failure.
 */
int no_args(t_token *token, int i)
{
	token->args = ft_calloc(2, sizeof(char *));
	if (!token->args)
		return (-1);
	token->args[0] = ft_strdup(token->command);
	if (!token->args[0])
		return (-1);
	token->args[1] = NULL;
	token->arg_count = 1;
	return (i);
}

