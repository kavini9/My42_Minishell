/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_unquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:01:13 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/07 17:33:58 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * if_check - Determines if the current character requires expansion.
 *
 * @cmd: Pointer to the current command structure.
 * @arg: Pointer to the expansion context.
 *
 * Checks for special characters like '$' or '~' that trigger variable expansion.
 * Returns 1 if expansion is needed, 0 otherwise.
 */
static int if_check(t_cmd *cmd, t_expand *arg)
{
	if ((cmd->seg[arg->i] == '~' && (cmd->seg[arg->i + 1] == '/'
		|| ft_isspace(cmd->seg[arg->i + 1]) || !cmd->seg[arg->i + 1]))
		|| (cmd->seg[arg->i] == '$' && (cmd->seg[arg->i + 1]
		&& (ft_isalnum(cmd->seg[arg->i + 1])
			|| cmd->seg[arg->i + 1] == '_' || cmd->seg[arg->i + 1] == '?'))))
		return (1);
	return (0);
}

/**
 * expand_var - Expands a `$VAR`, `$?`, or `~` from the input string.
 *
 * @msh: Pointer to the shell structure.
 * @str: The input string containing the variable.
 * @expan: Pointer to the result string accumulating expansion.
 * @arg: Pointer to the expansion context.
 *
 * Calls variable or tilde expansion logic and updates position.
 * Returns new index or -1 on failure.
 */
static int expand_var(t_msh *msh, char *str, char **expan, t_expand *arg)
{
	int cont = arg->i;

	arg->start = arg->i;
	if (str[arg->i] == '$')
		arg->i = oh_a_dollar(msh, str, expan, arg);
	if (arg->i == -1)
		return (-1);
	else if (str[arg->i] == '~')
		arg->i = tildes_home(msh, str, expan, arg);
	if (str[cont + 1] == '?')
		arg->i = cont + 2;
	return (arg->i);
}

/**
 * this_expands - Handles `$VAR` or `~` expansion logic at the current index.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the command being parsed.
 * @arg: Pointer to the expansion context.
 *
 * Calls `expand_var()` when expansion is needed.
 * Returns updated index or -1 on error.
 */
static int this_expands(t_msh *msh, t_cmd *cmd, t_expand *arg)
{
	if ((cmd->seg[arg->i] == '~' && (cmd->seg[arg->i + 1] == '/'
		|| ft_isspace(cmd->seg[arg->i + 1]) || !cmd->seg[arg->i + 1]))
		|| (cmd->seg[arg->i] == '$' && (cmd->seg[arg->i + 1]
		&& (ft_isalnum(cmd->seg[arg->i + 1])
			|| cmd->seg[arg->i + 1] == '_' || cmd->seg[arg->i + 1] == '?'))))
		arg->i = expand_var(msh, cmd->seg, &arg->value, arg);
	if (arg->i == -1)
		return (-1);
	return (arg->i);
}

/**
 * no_quotes - Parses and expands an unquoted segment of the input.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the current command being expanded.
 * @i: Starting index in the input string.
 * @arg: Pointer to the expansion context.
 *
 * Expands variables or text until a quote or space is encountered.
 * Returns the updated index or -1 on error.
 */
int no_quotes(t_msh *msh, t_cmd *cmd, int i, t_expand *arg)
{
	the_arg(arg, i);
	if (!arg->value)
		return (-1);
	while (cmd->seg[arg->i])
	{
		if ((cmd->seg[arg->i] == '$'
			&& (cmd->seg[arg->i + 1] == '"' || cmd->seg[arg->i + 1] == '\'')) 
			&& !arg->dbl && !arg->sgl)
			arg->i++;
		if (ft_isspace(cmd->seg[arg->i]) || cmd->seg[arg->i] == '\''
			|| cmd->seg[arg->i] == '"')
			break;
		if (if_check(cmd, arg))
			arg->i = this_expands(msh, cmd, arg);
		else
			arg->i = no_expanding(msh, cmd->seg, arg);
		if (arg->i == -1)
			return (-1);
	}
	return (arg->i);
}

/**
 * s_unquoted - Handles the unquoted part of the command segment.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Double pointer to the command being parsed.
 * @arg: Pointer to the t_expand structure used for expansion.
 * @expan: Pointer to the string building the result.
 *
 * Calls `no_quotes()` to process plain text and apply any expansion.
 * Returns updated index or -1 on error.
 */
int s_unquoted(t_msh *msh, t_cmd **cmd, t_expand *arg, char **expan)
{
	char *temp = *expan;

	arg->i = no_quotes(msh, *cmd, arg->i, arg);
	if (arg->i == -1)
	{
		free(temp);
		*expan = NULL;
		return (-1);
	}
	*expan = ft_strjoin(temp, arg->value);
	free(temp);
	free(arg->value);
	arg->value = NULL;
	return (arg->i);
}

