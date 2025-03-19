/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:56:24 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/19 17:51:46 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * check_quotes - Checks for unclosed quotes within a given line.
 *
 * @line: The input string to check for unclosed quotes.
 * @limit: The index up to which to check for unclosed quotes (-1 for full string).
 *
 * This function scans through the input line to track the state of single (' ') 
 * and double (" ") quotes. If a quote character is encountered and it is not 
 * enclosed within the other type of quote, it toggles its corresponding flag.
 *
 * - If `limit` is `-1`, the function checks the entire line.
 * - If `limit` is specified, it checks only up to that index.
 *
 * Return: 1 if an unclosed quote is found, 0 otherwise.
 */
int	check_quotes(char *line, int limit)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (line[i] && (limit == -1 || i < limit))
	{
		if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	// Return 1 if there is an unclosed single or double quote
	return (single_quote || double_quote);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' )
	{
		return (1);
	}
	else
		return (0);
}

/**
 * is_this_empty - Checks if a given string consists only of whitespace.
 *
 * @input: The input string to check.
 *
 * This function iterates through the string and determines whether it 
 * contains only whitespace characters (spaces, tabs, newlines, etc.).
 * 
 * If a non-whitespace character is found, the function returns 0. 
 * Otherwise, if the string is empty or consists entirely of whitespace, 
 * it returns 1.
 *
 * Return: 1 if the string is NULL, empty, or only whitespace, 0 otherwise.
 */
int is_input_empty(const char *input)
{
    if (!input) // Check if the input pointer is NULL.
        return 1;

    while (*input)
    {
        if (!ft_isspace(*input)) // Check if the character is not a whitespace.
            return 0; // Input is not empty.
        input++;
    }
    return 1; // Input is empty.
}


int	skip_whitespace(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

