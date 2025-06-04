/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:56:24 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/04 16:40:07 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define FULL_LINE -1

int	 check_quote(char *line, int limit)
{
	int	single_quote = 0;
	int	double_quote = 0;
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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v');
}

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

int	skip_whitespace(char *str, int i)
{
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

