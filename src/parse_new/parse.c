/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:29:12 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/28 23:36:15 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int parse_line(msh)
{
    
}

int	msh_parse(char *line, t_msh *msh)
{
	if (build_command_structs(msh, line))
		return (1);
	if (split_line_by_pipe(line, msh))
		return (1);
	if (parse_line(msh))
		return (1);
	return (0);
}