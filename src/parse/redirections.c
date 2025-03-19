/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:25:32 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/19 18:56:05 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * validate_redirect - Ensures that a redirection operator is followed by a valid token.
 * @line: The input command string.
 * @msh: The shell structure for managing shell state and exit status.
 * @i: Pointer to the current index in the line.
 * @type: The redirection type (">", ">>", "<", "<<") used in error messages.
 *
 * This function skips whitespace after the redirection operator and verifies that
 * the next token is valid (not '|', '<', '>', or EOF). If invalid, it prints an
 * error message and updates the shell's exit code.
 *
 * Returns:
 * - 1 if the syntax is invalid.
 * - 0 if valid.
 */
static int validate_redirect(char *line, t_msh *msh, int *i, char *type)
{
	(*i)++;
	(*i) = skip_whitespace(line, *i);

	// Check for invalid tokens after the redirection operator
	if (!line[*i] || line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(type, 2);
		msh->exit_code = 2;
		return (1);
	}
	return (0);
}

/**
 * check_in_redir - Validates input redirection syntax.
 * @line: The input command string.
 * @msh: The shell structure for managing shell state and exit status.
 * @i: Pointer to the current index in the line.
 *
 * This function handles single ('>') and double ('>>') output redirection cases.
 * It ensures the redirection operator is followed by a valid token.
 *
 * Returns:
 * - 1 if an error is found.
 * - 0 if valid.
 */
static int check_in_redir(char *line, t_msh *msh, int *i)
{
	if (line[*i + 1] == '>')
	{
		(*i)++;
		if (validate_redirect(line, msh, i, ">>") != 0)
			return (1);
	}
	else
	{
		if (validate_redirect(line, msh, i, ">") != 0)
			return (1);
	}
	return (0);
}

/**
 * check_out_redir - Validates output redirection syntax.
 * @line: The input command string.
 * @msh: The shell structure for managing shell state and exit status.
 * @i: Pointer to the current index in the line.
 *
 * This function handles single ('<') and double ('<<') input redirection cases.
 * It ensures the redirection operator is followed by a valid token.
 *
 * Returns:
 * - 1 if an error is found.
 * - 0 if valid.
 */
static int check_out_redir(char *line, t_msh *msh, int *i)
{
	if (line[*i + 1] == '<')
	{
		(*i)++;
		if (validate_redirect(line, msh, i, "<<") != 0)
			return (1);
	}
	else
	{
		if (validate_redirect(line, msh, i, "<") != 0)
			return (1);
	}
	return (0);
}

/**
 * check_redirects - Scans the input line for redirection operators.
 * @line: The input command string.
 * @msh: The shell structure for managing shell state and exit status.
 *
 * This function detects redirection operators ('>' and '<') while ensuring
 * they are not inside quotes. If found, it calls helper functions to validate
 * their syntax and usage.
 *
 * Returns:
 * - 1 if a syntax error is detected.
 * - 0 if redirections are valid.
 */
int check_redirects(char *line, t_msh *msh)
{
	int i;

	i = 0;
	while (line[i])
	{
		// Check for output redirection ('>') while ensuring it's outside quotes
		if (line[i] == '>' && !check_quotes(line, i))
		{
			if (check_in_redir(line, msh, &i))
				return (1);
		}
		// Check for input redirection ('<') while ensuring it's outside quotes
		else if (line[i] == '<' && !check_quotes(line, i))
		{
			if (check_out_redir(line, msh, &i))
				return (1);
		}
		i++;
	}
	return (0);
}