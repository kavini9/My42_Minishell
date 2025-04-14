/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:33:32 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/14 23:44:32 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static int  is_option(char *arg)
{
    if (*arg == '-' && *(arg + 1))
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
        printf_fd(STDOUT_FILENO, "%s", *cmd);//TODO: change printf to fd_putstr_fd pr printf_fd
        if (*(cmd + 1))
            printf_fd(STDOUT_FILENO, " ");//TODO: change printf to fd_putstr_fd or printf_fd
        cmd++;
    }
    if (!opt_n)
        printf_fd(STDOUT_FILENO, "\n");//TODO: change printf to fd_putstr_fd or printf_fd
    msh -> exit_code = EXIT_SUCCESS;
}

//TODO: find a way to update exit status