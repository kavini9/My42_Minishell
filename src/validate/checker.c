/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:56:24 by aoshinth          #+#    #+#             */
/*   Updated: 2025/05/31 18:59:11 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define FULL_LINE -1

/**
 * 
 * - Checks for unclosed quotes within a given line.
 *
 * @line: The input string to check for unclosed quotes.
 * @limit: The index up to which to check for unclosed quotes (-1 for full string).
 *
 * This function scans through the input line to track the state of single (' ') 
 * and double (" ") quotes. If a quote character is encountered and it is not 
 * enclosed within the other type of quote, it toggles its corresponding flag.
 *
 * Return: 1 if an unclosed quote is found, 0 otherwise.
 */
int	 check_quote(char *line, int limit)
{
	int	single_quote = 0;//1
	int	double_quote = 0;//0
	int	i = 0;

	while (line[i] && (limit == FULL_LINE || i < limit))
	{
		if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote; 
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote; 
		i++;
	}
	return (single_quote || double_quote);
}

/**
 * ft_isspace - Checks whether a character is a whitespace character.
 * 
 * @c: The character to check.
 * 
 * Return: 1 if the character is a whitespace, 0 otherwise.
 */
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v');
}

/**
 * is_input_empty - Checks if a given string consists only of whitespace.
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
	if (!input)
		return (1);
	while (*input)
	{
		if (!ft_isspace(*input))
			return (0);
		input++;
	}
	return (1);
}

/**
 * skip_whitespace - Skips over any leading whitespace in a string.
 *
 * @str: The input string.
 * @i: The index to start checking from.
 *
 * Return: The index of the first non-whitespace character.
 */
int	skip_whitespace(char *str, int i)
{
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

