/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:45:43 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/28 16:46:52 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * this_breaks - Determines if the current character should end the segment.
 *
 * @arg: Pointer to the t_expand structure tracking the current state.
 * @str: The input command string.
 *
 * Checks for whitespace or quotes, which typically terminate a word or segment.
 * Returns 1 if the segment should end, 0 otherwise.
 */
static int this_breaks(t_expand *arg, char *str)
{
	if (ft_isspace(str[arg->i]) || str[arg->i] == '\'' || str[arg->i] == '"')
		return (1);
	return (0);
}

/**
 * no_expand_dollar - Evaluates whether to skip or expand a `$` symbol.
 *
 * @arg: Pointer to the t_expand structure tracking expansion state.
 * @str: The command input string.
 *
 * Decides if `$` should be ignored (e.g., in `$'`, `$"`), expanded (e.g., `$VAR`, `$?`),
 * or processed normally. Returns:
 * - 1 to skip expansion,
 * - 2 to expand,
 * - 0 for no special handling.
 */
static int no_expand_dollar(t_expand *arg, char *str)
{
	if (str[arg->i] == '$' && (str[arg->i + 1] == '"' || str[arg->i + 1] == '\'')
		&& !arg->dbl && !arg->sgl)
		return (1);
	if ((((arg->dbl && !arg->sgl) || (!arg->dbl && !arg->sgl))
		&& str[arg->i] == '$'
		&& ((str[arg->i + 1] && ft_isalnum(str[arg->i + 1]))
			|| str[arg->i + 1] == '?')))
		return (2);
	return (0);
}

/**
 * no_expanding - Handles a segment that may or may not include expansions.
 *
 * @msh: Pointer to the shell structure for environment context.
 * @str: The segment of the input being processed.
 * @arg: Pointer to the t_expand structure tracking the parsing state.
 *
 * Expands `$` variables if applicable, handles heredoc `<<`, and appends plain
 * characters to the result. Respects quoting and whitespace.
 * Returns updated index or -1 on error.
 */
int no_expanding(t_msh *msh, char *str, t_expand *arg)
{
	arg->sgl = 0;
	arg->dbl = 0;
	arg->start = arg->i;
	what_quote(str, arg);
	while (str[arg->i])
	{
		if (this_breaks(arg, str))
			break;
		if (no_expand_dollar(arg, str) == 1)
			arg->i++;
		else if (no_expand_dollar(arg, str) == 2)
		{
			if (we_have_dollar(msh, arg, str))
				return (-1);
		}
		else if (add_char(str, arg))
			return (-1);
		if (str[arg->i] == '<' && str[arg->i + 1] == '<')
		{
			arg->i = we_have_heredoc(arg, str, 1);
			if (arg->i == -1)
				return (-1);
		}
	}
	return (arg->i);
}
