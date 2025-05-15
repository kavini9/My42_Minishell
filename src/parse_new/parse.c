/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:29:12 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/06 16:25:20 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void line_split_bypipe(t_msh *msh, char *line, char **seg_arr)
{
    char *start;
    char *seg;
    char *temp;
    
    start = line;
    while (*line)
    {
        if (*line == '|' && !check_quotes(start, line))//change the check quotes function
        {
            seg = ft_substr(start, 0, line - start + 1);
            temp = seg;
            if (temp)
            {
                seg = ft_strtrim(temp, " \t\n\r\f\v");
                free(temp);
            }
            if (!seg)
                exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC.
            *seg_arr = seg;
            seg_arr++;
            start = line + 1;
        }
        line++;
    }
}

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
void	init_token(t_msh *msh, int cmd_count)
{
	msh -> aux -> token = ft_calloc(cmd_count + 1, sizeof(t_token **));
	if (!msh -> aux -> token)
		exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC. Free aux -> seg.
	while (cmd_count--)
	{
		*(msh -> aux -> token) = ft_calloc(1, sizeof(t_token *));
		if (!*(msh -> aux -> token))
			exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC. Since we calloced we can free until we find it NULL.
		(msh -> aux -> token)++;
	}
}

void init_parse_structs(t_msh *msh, char *line) 
{
	msh -> cmd_count = count_pipes(line) + 1;
	msh -> aux -> seg = ft_calloc(msh -> cmd_count + 1, sizeof(char *));
	if (!msh -> aux -> seg)
		exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
	init_token(msh, msh -> cmd_count);
}

int	msh_parse(char *line, t_msh *msh)
{
	t_parse	aux;//in static memory remember to assign to cmd struct before leaving this function.

	msh -> aux = &aux;
	init_parse_structs(msh, line);
	line_split_bypipe(msh, line, msh -> aux -> seg);
	seg_tokenize(msh);
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