/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:33:32 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/20 21:30:51 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static int  is_option(char *arg)
{
    if (*arg == '-')
        arg++;
    while(*arg)
    {
        if (*arg != 'n')
            return (0);
        arg++;
    }
    return (1);
}

void    builtin_echo(t_msh *msh, char **cmd)
{ 
    int    opt_n;
    
    opt_n = 0;
    while (++cmd)
    {
        if (is_option(*cmd))
            opt_n = 1;
        else
            break;
    }
    while (*cmd)
    {
        printf("%s", *cmd);
        if (*(cmd + 1))
            printf(" ");
    }
    if (opt_n)
        printf("\n");
}

//TODO: find a way to update exit status