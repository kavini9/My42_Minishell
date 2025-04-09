/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:09:47 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/07 17:29:02 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * this_is_quote - Handles quoted sections of an argument during parsing.
 *
 * @cmd: Pointer to the command structure.
 * @arg: Pointer to the t_expand structure holding the current parsing state.
 *
 * Adds a quoted character to the argument value and updates the quote state.
 * Returns the updated index in the command segment.
 */
static int	this_is_quote(t_cmd *cmd, t_expand *arg)
{
	char	*temp;

	if (!arg->sgl && !arg->dbl && (cmd->seg[arg->i] == '\''
			|| cmd->seg[arg->i] == '"'))
	{
		temp = arg->value;
		arg->value = ft_strjoin_char(temp, cmd->seg[arg->i]);
		what_quote(cmd->seg, arg);
		free(temp);
	}
	else if ((arg->sgl && cmd->seg[arg->i] == '\'')
		|| (arg->dbl && cmd->seg[arg->i] == '"'))
	{
		temp = arg->value;
		arg->value = ft_strjoin_char(arg->value, cmd->seg[arg->i]);
		what_quote(cmd->seg, arg);
		free(temp);
	}
	return (arg->i);
}

/**
 * export_args - Parses an argument for the `export` command.
 *
 * @cmd: Pointer to the command structure.
 * @arg: Pointer to the t_expand structure holding the argument being processed.
 * @i: Starting index in the command segment.
 *
 * Extracts an argument for the `export` command,
 * handling quoted values and adding
 * characters to the argument. Returns the updated index or -1 on failure.
 */
static int	export_args(t_cmd *cmd, t_expand *arg, int i)
{
	the_arg(arg, i);
	what_quote(cmd->seg, arg);
	while (cmd->seg[arg->i])
	{
		if (ft_isspace(cmd->seg[arg->i]) && !arg->sgl && !arg->dbl)
			break ;
		if (cmd->seg[arg->i] == '\'' || cmd->seg[arg->i] == '"')
			arg->i = this_is_quote(cmd, arg);
		else if (add_char(cmd->seg, arg))
			return (free(arg->value), -1);
	}
	return (arg->i);
}

/**
 * handle_export_redir - Handles arguments specific to
 *                       `export` command with redirection.
 *
 * @cmd: Pointer to the command structure.
 * @arg: Pointer to the t_expand structure holding the argument being processed.
 * @i: Current index in the command segment.
 * @index: Pointer to the current argument index in the command's cmd array.
 *
 * Processes redirection arguments for `export`
 * and appends them to the cmd array.
 * Returns the updated index or -1 on failure.
 */
static int	handle_export_redir(t_cmd *cmd, t_expand *arg, int i, int *index)
{
	i = export_args(cmd, arg, i);
	if (!arg->value || append_to_array(cmd, arg->value, index) == -1)
	{
		free(arg->value);
		ft_free_array(cmd->cmd);
		return (-1);
	}
	free(arg->value);
	i = skip_whitespace(cmd->seg, i);
	return (i);
}

/**
 * handle_arg - Processes a single argument from the command segment.
 *
 * @cmd: Pointer to the command structure.
 * @i: Current index in the command segment.
 * @arg: Pointer to the t_expand structure holding the parsed argument.
 * @arg_index: Pointer to the current argument index in the command's cmd array.
 *
 * Handles arguments enclosed in quotes or unquoted arguments.
 * For the `export` command,
 * also processes redirection arguments.
 * Appends the processed argument to the cmd array.
 * Returns the updated index or -1 on failure.
 */
static int	handle_arg(t_cmd *cmd, int i, t_expand *arg, int *arg_index)
{
	if (ft_strcmp(cmd->command, "export") == 0 && only_redirect(cmd->seg, i))
	{
		i = handle_export_redir(cmd, arg, i, arg_index);
		if (i == -1)
			return (-1);
		return (i);
	}
	if (cmd->seg[i] == '\'' || cmd->seg[i] == '"')
		i = arg_in_quotes(cmd->seg, i, arg);
	else if (!ft_isspace(cmd->seg[i]) || !is_redirection(cmd, i))
		i = arg_no_quotes(cmd, arg, i);
	if (i == -1)
		return (-1);
	if (!arg->value || append_to_array(cmd, arg->value, arg_index) == -1)
	{
		free(arg->value);
		ft_free_array(cmd->cmd);
		return (-1);
	}
	free(arg->value);
	i = skip_whitespace(cmd->seg, i);
	return (i);
}

/**
 * handle_cmd_args - Parses and processes the command arguments.
 *
 * @msh: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @i: Starting index in the command segment.
 *
 * Allocates memory for the command's arguments and iterates through the command
 * segment to extract arguments. Handles redirections,
 * quoted arguments, and whitespace.
 * Returns the updated index on success or -1 on failure.
 */
int	handle_cmd_args(t_msh *msh, t_cmd *cmd, int i)
{
	int			arg_index;
	t_expand	arg;

	if (init_args_array(cmd, i) == -1)
		return (-1);
	arg_index = 1;
	i = skip_whitespace(cmd->seg, i);
	the_arg(&arg, i);
	free(arg.value);
	while (cmd->seg[i] && arg_index < cmd->cmd_index + 1)
	{
		if (is_redirection(cmd, i))
		{
			i = handle_redirections(msh, cmd, i);
			if (i == -1)
				return (-1);
			i = skip_whitespace(cmd->seg, i);
			continue ;
		}
		i = handle_arg(cmd, i, &arg, &arg_index);
		if (i == -1)
			return (-1);
	}
	cmd->cmd[arg_index] = NULL;
	return (i);
}
