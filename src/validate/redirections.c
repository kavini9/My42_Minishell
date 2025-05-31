/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:25:32 by aoshinth          #+#    #+#             */
/*   Updated: 2025/05/31 19:01:14 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Validates syntax after a redirection operator in the input line.
 *
 * This function checks whether the token following a redirection operator
 * (such as '<', '>', '>>', '<<') is valid. According to shell syntax rules,
 * a redirection cannot be immediately followed by a pipe ('|'), another
 * redirection symbol, or the end of input. If such an invalid token is found,
 * it prints a bash-like error message to stderr and updates the shell's
 * exit code accordingly.
 *
 * @param line The full input line from the user.
 * @param msh  Pointer to the main shell structure (used to set exit_code).
 * @param i    Pointer to the current index in the input string (will be advanced).
 * @param type A string representing the redirection type (used for better error messages).
 *
 * @return int Returns 1 if a syntax error is detected, 0 if the syntax is valid.
 */
int validate_redirect(char *line, t_msh *msh, int *i, char *type)
{
	(*i)++;
	(*i) = skip_whitespace(line, *i);

	// Check for invalid characters immediately after redirection
	if (!line[*i] || line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!line[*i])
			ft_putstr_fd("newline", 2);
		else if (type)
			ft_putstr_fd(type, 2);  // Use provided redirection type if available
		else
			write(2, &line[*i], 1); // Otherwise, print the invalid character
		ft_putstr_fd("'\n", 2);

		msh->exit_code = 2;
		return (1);
	}
	return (0);
}


/**
 * check_in_redirects - Validates output redirection syntax ('>' and '>>').
 * @line: The input command string.
 * @msh: The shell structure for managing shell state and exit status.
 * @i: Pointer to the current index in the line.
 *
 * This function handles both single ('>') and double ('>>') output redirections.
 * It ensures that each redirection operator is correctly followed by a valid token.
 *
 * Returns:
 * - 1 if a syntax error is detected.
 * - 0 if valid.
 */
static int check_in_redirects(char *line, t_msh *msh, int *i)
{
	if (line[*i + 1] == '>')
	{
		(*i)++;
		if (validate_redirect(line, msh, i, ">>"))
			return (1);
	}
	else
	{
		if (validate_redirect(line, msh, i, ">"))
			return (1);
	}
	return (0);
}

/**
 * check_out_redirects - Validates input redirection syntax ('<' and '<<').
 * @line: The input command string.
 * @msh: The shell structure for managing shell state and exit status.
 * @i: Pointer to the current index in the line.
 *
 * This function handles both single ('<') and double ('<<') input redirections.
 * It ensures that each redirection operator is correctly followed by a valid token.
 *
 * Returns:
 * - 1 if a syntax error is detected.
 * - 0 if valid.
 */
static int check_out_redirects(char *line, t_msh *msh, int *i)
{
	if (line[*i + 1] == '<')
	{
		(*i)++;
		if (validate_redirect(line, msh, i, "<<"))
			return (1);
	}
	else
	{
		if (validate_redirect(line, msh, i, "<"))
			return (1);
	}
	return (0);
}

/**
 * check_redirects - Scans the input line for redirection operators ('>' and '<').
 * @line: The input command string.
 * @msh: The shell structure for managing shell state and exit status.
 *
 * This function detects redirection operators while ensuring they are not inside
 * quotes. If a redirection is found, it calls helper functions to validate syntax.
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
		if (line[i] == '>' && !check_quote(line, i))
		{
			if (check_in_redirects(line, msh, &i))
				return (1);
		}
		// Check for input redirection ('<') while ensuring it's outside quotes
		else if (line[i] == '<' && !check_quote(line, i))
		{
			if (check_out_redirects(line, msh, &i))
				return (1);
		}
		i++;
	}
	return (0);
}
