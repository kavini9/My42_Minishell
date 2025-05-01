/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:27:41 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/01 15:55:39 by wweerasi         ###   ########.fr       */
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
                seg = ft_strtrim(temp, " \t\n\r\v");
            free(temp);
            if (!seg)
                printf("error segmenting the line by pipe\n");//TODO:error handling
            *seg_arr = seg;
            seg_arr++;
            start = line + 1;
        }
        line++;
    }
}