/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:56:24 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/18 15:30:54 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"
# include "parse.h"

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


int	is_this_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

int	skip_whitespace(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}