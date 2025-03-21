/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:26:27 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/21 21:05:05 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static void    display_x_var(char **envl, char floor)
{
    char    **lex_min;
    char    **iter;
    int len;
    
    iter = envl;
    len = 0;
    while (iter[len])
        len++;
    while(len--)
    {
        lex_min = envl;
        iter = envl;
        while(*lex_min && ft_strcmp(*lex_min, floor) > 0)
            lex_min++;
        while (*iter)
        {
            if(ft_strcmp(*lex_min, *iter) > 0 && ft_strcmp(*iter, floor) > 0 )
                lex_min = iter;
            iter++;
        }
        printf_fd(STDOUT_FILENO, "declare -x %s\n", *lex_min);
        floor = lex_min;
    }  
}

void    builtin_export(t_msh *msh, char **cmd)
{
    if (!*(++cmd))
        return (display_x_var(msh -> envl, ""));
    while (*cmd)
    {
        if(!is_valid_id(*cmd))
            printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", *cmd);
        else
            set_x_var(*cmd);  
    }
}
