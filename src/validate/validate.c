/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:30 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 09:46:42 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_pipe_position(t_msh *msh, char *line, int i)
{
	int	j;

	j = skip_whitespace(line, i + 1);
	if (line[j] == '|' && !check_quote(line, j))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		msh->exit_code = 2;
		return (1);
	}
	return (0);
}

static int	detect_consecutive_pipes(t_msh *msh, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && !check_quote(line, i))
		{
			if (validate_pipe_position(msh, line, i))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	handle_trailing_pipe(t_msh *msh, char *line)
{
	int		i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_isspace(line[i]))
		i--;
	if (i >= 0 && line[i] == '|')
	{
		if (i >= 1 && (line[i - 1] == '>' || line[i - 1] == '<'))
			check_redirects(msh, line);
		else
			ft_putendl_fd(
				"minishell: syntax error near unexpected token `|'", 2);
		msh->exit_code = 2;
		return (1);
	}
	return (0);
}

int	validate_pipe(t_msh *msh, char *line)
{
	int	i;
	int	j;
	int	len;

	i = skip_whitespace(line, 0);
	if (line[i] == '|' && !check_quote(line, i))
	{
		j = i;
		while (line[j] == '|')
			j++;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		len = j - i;
		if (len > 2)
			len = 2;
		write(2, line + i, len);
		ft_putendl_fd("'", 2);
		msh->exit_code = 2;
		return (1);
	}
	if (detect_consecutive_pipes(msh, line) || handle_trailing_pipe(msh, line))
		return (1);
	return (0);
}

int	msh_validate_line(t_msh *msh, char **line)
{
	int	i;	

	i = 0;
	if (!**line || !(*line)[skip_whitespace(*line, i)])
		return (1);
	if (check_quote(*line, ft_strlen(*line)))
	{
		ft_putendl_fd("minishell: syntax error unmatched quotes", 2);
		msh->exit_code = 2;
		return (1);
	}
	if (validate_pipe(msh, *line))
		return (1);
	while ((*line)[i])
	{
		if (!check_quote(*line, i) && ((*line)[i] == ';' || (*line)[i] == '\\'))
		{
			ft_putendl_fd("minishell: invalid syntax", 2);
			msh->exit_code = 2;
			return (1);
		}
		i++;
	}
	return (check_redirects(msh, *line));
}
