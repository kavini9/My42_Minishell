/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:02:37 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/28 17:05:11 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	 check_quotes(char *start, char *end)
{
	int	single_quote = 0;
	int	double_quote = 0;

    while (*start && start != end)
	{
		if (*start == '\'' && !double_quote)
			single_quote = !single_quote * (int) *start ; 
		else if (*start == '"' && !single_quote)
			double_quote = !double_quote * (int) *start; 
		start++;
	}
	return (single_quote || double_quote);
}

void skip_whitespaces(char **str)
{
    while (**str && ft_strchr(" \t\n\r\f\v", **str))
        (*str)++;
}