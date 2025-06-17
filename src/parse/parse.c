/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:29:12 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 04:38:43 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	line_split_bypipe(t_msh *msh, char *line, char *start, char **seg_arr)
{
	char	*seg;
	char	*temp;

	while (*line)
	{
		if ((*(line + 1) == '|' || !*(line + 1))
			&& !check_quotes(start, line + 1))
		{
			seg = ft_substr(start, 0, line - start + 1);
			temp = seg;
			if (temp)
			{
				seg = ft_strtrim(temp, " \t\n\r\f\v");
				free(temp);
			}
			if (!seg)
				parse_error(msh, msh -> aux, NULL, "line_split");
			*seg_arr = seg;
			seg_arr++;
			if (*(line + 1))
				start = line + 2;
		}
		line++;
	}
}

int	count_pipes(char *line)
{
	int		pipe_count;
	char	*start;

	pipe_count = 0;
	start = line;
	while (*line)
	{
		if (*line == '|' && !check_quotes(start, line + 1))
			pipe_count++;
		line++;
	}
	return (pipe_count);
}

void	init_parse_structs(t_msh *msh, char *line)
{
	msh -> cmd_count = count_pipes(line) + 1;
	msh -> aux -> line = &line;
	msh -> aux -> seg = ft_calloc(msh -> cmd_count + 1, sizeof(char *));
	if (!msh -> aux -> seg)
		parse_error(msh, msh -> aux, NULL, "init_parse");
	msh -> aux -> token = ft_calloc(msh -> cmd_count + 1, sizeof(t_token *));
	if (!msh -> aux -> token)
		parse_error(msh, msh -> aux, NULL, "init_parse");
}
//MALLOC FAIL PROTECTION: CHECKED. except for case: line 81
//see how line gets freed if MALLOC fails