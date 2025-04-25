/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:40:33 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/28 16:41:21 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * just_a_quest - Handles expansion of the special variable `$?`.
 *
 * @str: The input string being parsed.
 * @name: Buffer to store the resulting variable name (i.e., "?").
 * @indx: Pointer to the current index in the name buffer.
 * @arg: Pointer to the t_expand structure tracking parsing state.
 *
 * If the current character is '?', appends it to the name buffer
 * and advances the parsing index.
 */
void just_a_quest(char *str, char *name, int *indx, t_expand *arg)
{
	if (str[arg->i] == '?')
	{
		if (*indx < (int)sizeof(name) - 1)
			name[(*indx)++] = str[arg->i++];
	}
	name[*indx] = '\0';
}

/**
 * we_need_name - Extracts a valid variable name after a '$' character.
 *
 * @arg: Pointer to the t_expand structure tracking the current index.
 * @str: The input string containing the variable.
 * @name: Buffer to store the extracted variable name.
 * @indx: Pointer to the index for writing into the name buffer.
 *
 * Reads characters following '$' and stores alphanumeric or underscore
 * characters into the `name` buffer until an invalid character is found.
 * Null-terminates the result.
 */
void we_need_name(t_expand *arg, char *str, char *name, int *indx)
{
	while (str[arg->i] && (ft_isalnum(str[arg->i]) || str[arg->i] == '_'))
	{
		if (*indx < 100 - 1)
			name[(*indx)++] = str[arg->i++];
	}
	name[*indx] = '\0';
}

