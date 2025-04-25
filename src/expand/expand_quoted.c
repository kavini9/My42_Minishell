/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:43:28 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/28 16:45:17 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_quoted - Prepares the expansion context to enter a quoted section.
 *
 * @arg: Pointer to the t_expand structure tracking expansion state.
 * @i: Starting index of the quoted segment.
 * @str: Input string being processed.
 *
 * Initializes expansion and appends the first quote character.
 * Returns the current index on success, -1 on failure.
 */
static int init_quoted(t_expand *arg, int i, char *str)
{
	char *temp;

	if (the_arg(arg, i))
		return (-1);
	temp = arg->value;
	arg->value = ft_strjoin_char(temp, str[arg->i]);
	free(temp);
	if (!arg->value)
		return (-1);
	return (arg->i);
}

/**
 * handle_dollar - Expands variables prefixed with `$` in quoted context.
 *
 * @msh: Pointer to the shell structure for accessing environment.
 * @arg: Pointer to the expansion context.
 * @str: The input string being parsed.
 *
 * Performs expansion if inside double quotes or unquoted;
 * skips expansion if inside single quotes.
 * Returns updated index or -1 on error.
 */
static int handle_dollar(t_msh *msh, t_expand *arg, char *str)
{
	if (str[arg->i] == '$' && str[arg->i + 1]
		&& (str[arg->i + 1] == '\'' || str[arg->i + 1] == '"')
		&& (!arg->sgl && !arg->dbl))
		arg->i++;
	if ((str[arg->i] == '$' && !arg->sgl) && str[arg->i + 1]
		&& !ft_isspace(str[arg->i + 1])
		&& (ft_isalnum(str[arg->i + 1]) || str[arg->i + 1] == '_'
			|| str[arg->i + 1] == '?'))
	{
		if (we_have_dollar(msh, arg, str) == -1)
			return (-1);
	}
	return (arg->i);
}

/**
 * handle_quotes - Toggles quote state and appends quote characters.
 *
 * @arg: Pointer to the expansion context.
 * @str: Input string being processed.
 *
 * Adds quote characters to the expanded result and updates quote flags.
 * Returns updated index or -1 on failure.
 */
static int handle_quotes(t_expand *arg, char *str)
{
	char *temp;

	if (!arg->sgl && !arg->dbl && (str[arg->i] == '\'' || str[arg->i] == '"'))
		what_quote(str, arg);
	else if ((arg->sgl && str[arg->i] == '\'') || (arg->dbl && str[arg->i] == '"'))
	{
		temp = arg->value;
		arg->value = ft_strjoin_char(temp, str[arg->i]);
		what_quote(str, arg);
		free(temp);
	}
	return (arg->i);
}

/**
 * we_have_heredoc - Extracts a heredoc delimiter string from input.
 *
 * @arg: Pointer to the expansion context.
 * @str: Input string containing the heredoc segment.
 * @n: Flag to control whether to reinitialize the value field.
 *
 * Scans and collects characters from heredoc segment into arg->value.
 * Returns updated index or -1 on error.
 */
int we_have_heredoc(t_expand *arg, char *str, int n)
{
	if (!n)
		arg->value = ft_strdup("");
	while (str[arg->i] == '<' || ft_isspace(str[arg->i]))
	{
		if (add_char(str, arg))
			return (-1);
	}
	while (str[arg->i] && (!ft_isspace(str[arg->i])
		|| !(str[arg->i] == '<') || !(str[arg->i] == '>')))
	{
		if (add_char(str, arg))
			return (-1);
	}
	return (arg->i);
}

/**
 * in_quotes - Parses and expands a quoted segment.
 *
 * @msh: Pointer to the shell structure.
 * @str: Input string containing the quoted section.
 * @i: Index where the quote begins.
 * @arg: Pointer to the t_expand structure.
 *
 * Handles variable expansion inside quotes, respecting quote states.
 * Returns the index after processing or -1 on failure.
 */
int in_quotes(t_msh *msh, char *str, int i, t_expand *arg)
{
	if (init_quoted(arg, i, str) == -1)
		return (-1);
	what_quote(str, arg);
	while (str[arg->i])
	{
		if (!arg->sgl && !arg->dbl)
			break;
		if (arg->i != -1 && str[arg->i] == '$')
			arg->i = handle_dollar(msh, arg, str);
		if (arg->i != -1 && ((!arg->sgl && !arg->dbl && (str[arg->i] == '\''
			|| str[arg->i] == '"')) || (arg->sgl && str[arg->i] == '\'')
			|| (arg->dbl && str[arg->i] == '"')))
			arg->i = handle_quotes(arg, str);
		else if (arg->i != -1)
		{
			if (add_char(str, arg))
				return (-1);
		}
		if (arg->i == -1)
			return (-1);
	}
	return (arg->i);
}
