/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:27 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/27 19:53:31 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_cmd(t_cmd *cmd)
{
    t_redir *redir_list;
    
    while (cmd)
    {
        if (cmd -> cmd)
            free_arr(cmd -> cmd);
        redir_list = cmd -> redir;
        while (redir_list)
        { 
            free(redir_list -> fname_o_del);
            if (redir_list -> expand)
                free(redir_list -> expand);
            redir_list = redir_list -> next; //did not free the t_redir struct assuming it is not allocated since it has a type value and two pointers.
        }
        ft_memset(cmd, 0, sizeof(t_cmd));
        cmd++;
    }
}

void msh_clean(t_msh *msh)
{
    if (msh -> cwd)
        free(msh -> cwd);
    if (msh -> old_wd)
        free(msh -> old_wd);
    if (msh -> envl)
        free_arr(msh -> envl);
    if (msh -> cmd);
        free_cmd(msh -> cmd);
    ft_memset(msh, 0, offsetof(t_msh, exit_code));
}
