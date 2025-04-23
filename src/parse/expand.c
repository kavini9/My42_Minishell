/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:32:32 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/22 16:00:33 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * this_is_space - Appends a space character from the segment to the result.
 *
 * @cmd: Double pointer to the current command segment.
 * @arg: Expansion context pointer.
 * @expan: Pointer to the string being built.
 *
 * Return: Updated index or -1 on allocation failure.
 */
static int	this_is_space(t_cmd **cmd, t_expand *arg, char **expan)
{
	char *temp;

	temp = *expan;
	*expan = ft_strjoin_char(temp, (*cmd)->seg[arg->i]);
	free(temp);
	if (!*expan)
		return (-1);
	arg->i++;
	return (arg->i);
}

/**
 * hd - Handles heredoc expansion from the segment.
 *
 * @cmd: Double pointer to the command being processed.
 * @arg: Expansion context pointer.
 * @expan: Pointer to the string being built.
 *
 * Appends heredoc content from `arg->value` to the expanded string.
 *
 * Return: Updated index or -1 on failure.
 */
static int	hd(t_cmd **cmd, t_expand *arg, char **expan)
{
	char *temp;

	temp = *expan;
	arg->i = we_have_heredoc(arg, (*cmd)->seg, 0);
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
 * @cmd: Double pointer to the command being processed.
 * @arg: Expansion context pointer.
 * @expan: Pointer to the string being built.
 *
 * Handles quoted content and appends it to the expanded result.
 *
 * Return: Updated index or -1 on failure.
 */
static int	quoted(t_msh *msh, t_cmd **cmd, t_expand *arg, char **expan)
{
	char *temp;

	temp = *expan;
	arg->i = in_quotes(msh, (*cmd)->seg, arg->i, arg);
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
 * exp_while - Processes a segment and builds the expanded result.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Double pointer to the command being processed.
 * @arg: Pointer to the expansion context.
 * @expan: Pointer to the resulting expanded string.
 *
 * Loops through the segment and handles each character or section:
 * spaces, quotes, heredocs, or unquoted text.
 *
 * Return: 0 on success, 1 on failure.
 */
static int	exp_while(t_msh *msh, t_cmd **cmd, t_expand *arg, char **expan)
{
	while ((*cmd)->seg[arg->i])
	{
		if (arg->i != -1 && ft_isspace((*cmd)->seg[arg->i]) && !arg->dbl && !arg->sgl)
			arg->i = this_is_space(cmd, arg, expan);
		else if (arg->i != -1 && ((*cmd)->seg[arg->i] == '\'' || (*cmd)->seg[arg->i] == '"'))
			arg->i = quoted(msh, cmd, arg, expan);
		else if (arg->i != -1 && (*cmd)->seg[arg->i] == '<' && (*cmd)->seg[arg->i + 1] == '<')
			arg->i = hd(cmd, arg, expan);
		else if (arg->i != -1)
			arg->i = s_unquoted(msh, cmd, arg, expan);
		if (arg->i == -1)
			return (1);
	}
	return (0);
}

/**
 * handle_expand - Expands variables, quotes, and heredocs in the segment.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Double pointer to the command structure.
 *
 * Performs command segment expansion and replaces the original segment
 * with the expanded result.
 *
 * Return: 0 on success, 1 on failure.
 */
int	handle_expand(t_msh *msh, t_cmd **cmd)
{
	t_expand	arg;
	char		*expan;

	expan = NULL;
	if (init_expansion(&arg, &expan))
		return (1);
	if (exp_while(msh, cmd, &arg, &expan))
	{
		if (arg.value)
			free(arg.value);
		if (expan)
			free(expan);
		return (1);
	}
	free((*cmd)->seg);
	(*cmd)->seg = expan;
	return (0);
}

