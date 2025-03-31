/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:39:03 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/28 16:40:18 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * what_quote - Updates quote state in the t_expand structure.
 *
 * @str: The input string being parsed.
 * @arg: Pointer to the t_expand structure tracking quote states and index.
 *
 * Toggles quote flags (single or double) when encountering quote characters.
 * Advances `arg->i` appropriately.
 */
void what_quote(char *str, t_expand *arg)
{
	if ((arg->sgl && str[arg->i] == '\'') || (arg->dbl && str[arg->i] == '"'))
	{
		if (str[arg->i] == '\'')
			arg->sgl = 0;
		else if (str[arg->i] == '"')
			arg->dbl = 0;
		arg->i++;
		return;
	}
	if (str[arg->i] == '\'' && !arg->sgl)
	{
		arg->sgl = 1;
		arg->i++;
		return;
	}
	if (str[arg->i] == '"' && !arg->dbl)
	{
		arg->dbl = 1;
		arg->i++;
	}
}

/**
 * new_result - Joins the current result with a new string segment.
 *
 * @arg: Pointer to the t_expand structure holding the result.
 * @temp: Newly allocated string segment to append.
 *
 * Concatenates `arg->value` with `temp`, replaces the old result,
 * and frees both temporary strings. Returns 0 on success, -1 on failure.
 */
int new_result(t_expand *arg, char *temp)
{
	char *new_res = ft_strjoin(arg->value, temp);

	if (!new_res)
	{
		free(temp);
		return (-1);
	}
	free(arg->value);
	arg->value = new_res;
	free(temp);
	return (0);
}

/**
 * handle_question - Handles the special variable `$?` during expansion.
 *
 * @msh: Pointer to the shell structure for accessing exit status.
 * @str: The input string.
 * @expan: Pointer to the string accumulating the expansion result.
 * @arg: Pointer to the t_expand structure tracking position.
 *
 * Calls `oh_a_dollar()` and moves past the `?`. Returns updated index.
 */
int handle_question(t_msh *msh, char *str, char **expan, t_expand *arg)
{
	int cont = arg->i;

	arg->start = arg->i;
	if (str[arg->i] == '$')
		arg->i = oh_a_dollar(msh, str, expan, arg);
	arg->i = cont + 2;
	return (arg->i);
}

/**
 * the_arg - Initializes the t_expand structure for variable expansion.
 *
 * @arg: Pointer to the t_expand structure to initialize.
 * @i: Initial index to start from in the input string.
 *
 * Sets quote flags to 0, sets index tracking, and allocates an empty
 * string to hold the expansion result. Returns 0 on success, 1 on failure.
 */
int the_arg(t_expand *arg, int i)
{
	arg->sgl = 0;
	arg->dbl = 0;
	arg->i = i;
	arg->start = i;
	arg->name = NULL;
	arg->value = ft_strdup("");
	if (!arg->value)
	{
		ft_putendl_fd("Malloc fail", 2);
		return (1);
	}
	return (0);
}

/**
 * init_expansion - Sets up initial context for expanding a command segment.
 *
 * @arg: Pointer to the t_expand structure to initialize.
 * @expan: Pointer to the result string (set to an empty string).
 *
 * Allocates an empty string to `*expan`, initializes `arg`, and frees
 * its initial value (only used to test allocation success).
 *
 * Return: 0 on success, 1 on allocation failure.
 */
int init_expansion(t_expand *arg, char **expan)
{
	*expan = ft_strdup("");
	if (!*expan)
		return (1);
	the_arg(arg, 0);
	if (!arg->value)
	{
		free(*expan);
		return (1);
	}
	free(arg->value);
	arg->value = NULL;
	return (0);
}
