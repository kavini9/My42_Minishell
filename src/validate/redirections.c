/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:25:32 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/09 20:47:52 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int validate_redirect(t_msh *msh, char *line, int *i, char *type)
{
	
	(void) type;
	(*i)++;
	(*i) = skip_whitespace(line, *i);

	if (!line[*i] || line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!line[*i])
			ft_putstr_fd("newline", 2);
		else
			write(2, &line[*i], 1);
		ft_putstr_fd("'\n", 2);
		msh->exit_code = 2;
		return (1);
	}
	return (0);
}

static int check_in_redirects(t_msh *msh, char *line, int *i)
{
	int count;

	count = 1;
	while (line[*i + count] == '>')
		count++;
	if (count > 3)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
		msh->exit_code = 2;
		return (1);
	}
	if (count == 2)
	{
		(*i)++;
		if (validate_redirect(msh, line, i, ">>"))
			return (1);
	}
	else
	{
		if (validate_redirect(msh, line, i, ">"))
			return (1);
	}
	return (0);
}

static int check_out_redirects(t_msh *msh, char *line, int *i)
{
	int count;

	count = 1;
	while (line[*i + count] == '<')
		count++;
	if (count > 3)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
		msh->exit_code = 2;
		return (1);
	}
	if (count == 2)
	{
		(*i)++;
		if (validate_redirect(msh, line, i, "<<"))
			return (1);
	}
	else
	{
		if (validate_redirect(msh, line, i, "<"))
			return (1);
	}
	return (0);
}


int check_redirects(t_msh *msh, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' && !check_quote(line, i))
		{
			if (check_in_redirects(msh, line, &i))
				return (1);
		}
		else if (line[i] == '<' && !check_quote(line, i))
		{
			if (check_out_redirects(msh, line, &i))
				return (1);
		}
		i++;
	}
	return (0);
}