/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:02:37 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 09:22:49 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *start, char *end)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*start && start != end)
	{
		if (*start == '\'' && !double_quote)
			single_quote = !single_quote * ((int) *start);
		else if (*start == '"' && !single_quote)
			double_quote = !double_quote * ((int) *start);
		start++;
	}
	if (single_quote)
		return (single_quote);
	if (double_quote)
		return (double_quote);
	return (0);
}

char	*skip_whitespaces(char **str)
{
	while (**str && ft_strchr(" \t\n\r\f\v", **str))
		(*str)++;
	return (*str);
}

int	redir_skip(char *seg)
{
	int	skip;

	skip = 0;
	while (*seg && ft_strchr("< \t\n\r\f\v>", *seg))
	{
		skip++;
		seg++;
	}
	return (skip);
}

int	is_ambi_redir(char **expan, t_cmd *cmd, int len)
{
	if (ft_arrlen((void **) expan) > 1 || !**expan)
	{
		cmd -> redir[len]-> ambi_o_hdexp = 1;
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *q_arg)
{
	int		single_q;
	int		double_q;
	int		len;
	char	*arg;

	single_q = 0;
	double_q = 0;
	len = ft_strlen(q_arg);
	arg = q_arg;
	while (len--)
	{
		if (*q_arg == '\'' && !double_q)
		{
			single_q = !single_q;
			ft_memmove(q_arg, q_arg + 1, len + 1);
		}
		else if (*q_arg == '"' && !single_q)
		{
			double_q = !double_q;
			ft_memmove(q_arg, q_arg + 1, len + 1);
		}
		else
			q_arg++;
	}
	return (arg);
}
