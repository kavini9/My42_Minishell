/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:29:12 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/01 16:45:28 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(char *line)
{
	int	pipe_count;
	char *start;

	pipe_count = 0;
	start = line;
	while (*line)
	{
		if (*line == '|' && !check_quotes(start, line))
			pipe_count++;
		line++;
	}
	return (pipe_count);
}

int init_parse_structs(t_msh *msh, char *line)
{
	msh -> cmd_count = count_pipes(line) + 1;
	
    
}

int	msh_parse(char *line, t_msh *msh)
{
	if (init_parse_structs(msh, line))
		return (1);
	if (line_split_bypipe(msh, line, msh -> aux -> seg))
		return (1);
	if (parse_line(msh))
		return (1);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_msh	msh;
	(void) av;
	
	if (ac != 1)
		exit(printf("# minishell: Error: Invalid number of arguments."
		"\n# Usage: ./minishell"));
	msh_init(&msh, envp);
}