/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:13:21 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 14:34:45 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * parse_filename - Parses and extracts a filename from a command segment.
 *
 * @cmd:      Pointer to the command structure containing the segment to parse.
 * @i:        Index in the segment where filename parsing starts.
 * @filename: Pointer to a char pointer where the extracted filename will be stored.
 *
 * This function uses `filename_in_quotes` to extract the filename,
 * whether it is quoted or not. It duplicates the parsed value into `*filename`.
 * If memory allocation fails or parsing fails, it returns -1.
 * On success, it returns the updated index `i` after parsing the filename.
 */
int	parse_filename(t_cmd *cmd, int i, char **filename)
{
	t_expand	arg;

	arg.i = i;
	if (filename_in_quotes(cmd, cmd->seg, arg.i, &arg) == -1)
		return (-1);
	*filename = ft_strdup(arg.value);
	if (!*filename)
	{
		free(arg.value);
		ft_putendl_fd("Memory allocation for filename failed", 2);
		return (-1);
	}
	i = arg.i;
	free(arg.value);
	return (i);
}

/**
 * filename_in_quotes - Extracts a filename while respecting quotes.
 *
 * @cmd: Pointer to the command structure. Used for redirection property updates.
 * @str: The input segment string being parsed.
 * @i:   Current index in the input string.
 * @arg: Pointer to a t_expand structure to manage parsing state and extracted value.
 *
 * This function handles filenames enclosed in single or double quotes,
 * updating the `expand` flag in the command's redirection structure
 * to false if quotes are used. Parsing stops at whitespace or redirection
 * symbols ('<' or '>') outside of quotes. The parsed filename is stored
 * in `arg->value`, and `arg->i` is updated to the index after parsing.
 *
 * Returns the updated index on success, or -1 on failure.
 */
int	filename_in_quotes(t_cmd *cmd, char *str, int i, t_expand *arg)
{
	i = skip_whitespace(str, i);
	if (the_arg(arg, i))
		return (-1);
	what_quote(str, arg);
	if (arg->sgl == 1 || arg->dbl == 1)
		(cmd->redir_end)->expand = false;
	while (str[arg->i])
	{
		if ((ft_isspace(str[arg->i]) || str[arg->i] == '<' || str[arg->i] == '>')
			&& (!arg->sgl && !arg->dbl))
			break;
		else if (!arg->sgl && !arg->dbl && (str[arg->i] == '\'' || str[arg->i] == '"'))
			what_quote(str, arg);
		else if ((arg->sgl && str[arg->i] == '\'') || (arg->dbl && str[arg->i] == '"'))
			what_quote(str, arg);
		else if (add_char(str, arg))
			return (free(arg->value), -1);
	}
	return (arg->i);
}
