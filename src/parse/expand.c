/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:32:32 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/28 15:06:52 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * this_is_space - Appends a space character from the segment to the result.
 *
 * @token: Double pointer to the current token.
 * @arg: Expansion context pointer.
 * @expan: Pointer to the string being built.
 *
 * Return: Updated index or -1 on allocation failure.
 */
static int this_is_space(t_token **token, t_expand *arg, char **expan)
{
	char *temp;

	(void)token;
	temp = *expan;
	*expan = ft_strjoin_char(temp, (*token)->seg[arg->i]);
	free(temp);
	if (!*expan)
		return (-1);
	arg->i++;
	return (arg->i);
}

/**
 * hd - Handles heredoc expansion from the segment.
 *
 * @token: Double pointer to the token being processed.
 * @arg: Expansion context pointer.
 * @expan: Pointer to the string being built.
 *
 * Appends heredoc content from `arg->value` to the expanded string.
 *
 * Return: Updated index or -1 on failure.
 */
static int hd(t_token **token, t_expand *arg, char **expan)
{
	char *temp;

	temp = *expan;
	arg->i = we_have_heredoc(arg, (*token)->seg, 0);
	if (arg->i == -1)
		return (-1);
	*expan = ft_strjoin(temp, arg->value);
	if (!*expan)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	free(arg->value);
	arg->value = NULL;
	return (arg->i);
}

/**
 * quoted - Processes and expands a quoted section in the segment.
 *
 * @msh: Pointer to the shell structure.
 * @token: Double pointer to the token being processed.
 * @arg: Expansion context pointer.
 * @expan: Pointer to the string being built.
 *
 * Handles quoted content and appends it to the expanded result.
 *
 * Return: Updated index or -1 on failure.
 */
static int quoted(t_msh *msh, t_token **token, t_expand *arg, char **expan)
{
	char *temp;

	temp = *expan;
	arg->i = in_quotes(msh, (*token)->seg, arg->i, arg);
	if (arg->i == -1)
		return (-1);
	*expan = ft_strjoin(temp, arg->value);
	if (!*expan)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	free(arg->value);
	arg->value = NULL;
	return (arg->i);
}

/**
 * exp_while - Processes a segment and builds an expanded result.
 *
 * @msh: Pointer to the shell structure.
 * @token: Double pointer to the token being processed.
 * @arg: Pointer to expansion context.
 * @expan: Pointer to the resulting expanded string.
 *
 * Loops through the segment and handles each character or section:
 * space, quotes, heredocs, or unquoted text.
 *
 * Return: 0 on success, 1 on failure.
 */
static int exp_while(t_msh *msh, t_token **token, t_expand *arg, char **expan)
{
	while ((*token)->seg[arg->i])
	{
		if (arg->i != -1 && ft_isspace((*token)->seg[arg->i]) && !arg->dbl && !arg->sgl)
			arg->i = this_is_space(token, arg, expan);
		if (arg->i != -1 && ((*token)->seg[arg->i] == '\'' || (*token)->seg[arg->i] == '"'))
			arg->i = quoted(msh, token, arg, expan);
		if (arg->i != -1 && (*token)->seg[arg->i] == '<' && (*token)->seg[arg->i + 1] == '<')
			arg->i = hd(token, arg, expan);
		else if (arg->i != -1)
			arg->i = s_unquoted(msh, token, arg, expan);
		if (arg->i == -1)
			return (1);
	}
	return (0);
}

/**
 * handle_expand - Expands variables and processes special tokens in the segment.
 *
 * @msh: Pointer to the shell structure.
 * @token: Double pointer to the token structure.
 *
 * Performs command segment expansion, handling heredocs, quotes, and variables.
 * Replaces the original `seg` with the expanded result.
 *
 * Return: 0 on success, 1 on failure.
 */
int handle_expand(t_msh *msh, t_token **token)
{
	t_expand	arg;
	char		*expan;

	expan = NULL;
	if (init_expansion(&arg, &expan))
		return (1);
	if (exp_while(msh, token, &arg, &expan))
	{
		if (arg.value)
			free(arg.value);
		if (expan)
			free(expan);
		return (1);
	}
	free((*token)->seg);
	(*token)->seg = expan;
	return (0);
}
