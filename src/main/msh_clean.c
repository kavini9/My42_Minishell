/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:27 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/16 22:03:19 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_arr(void **arr)
{
    void **tmp;

    tmp = arr;
    while (*tmp)
    {
        free(*tmp);
        tmp++;
    }
    free(arr);
}

void    free_redir(t_redir **redir)
{
    t_redir **ptr_redir;
    
    ptr_redir = redir;
    if (!redir)
        return ;
    while (redir && *redir)
    { 
        free((*redir) -> fname_o_del);//should we checkk if this exist.
        free(*redir);
        redir++;
    }
    free(ptr_redir);
}

void    free_cmd(t_cmd **cmd)
{
    t_cmd **cmd_ptr;
    
    cmd_ptr = cmd;
    while (*cmd)
    {
        if ((*cmd) -> cmd)
            free_arr((void **) (*cmd) -> cmd);
        if ((*cmd) -> redir)
            free_redir((*cmd) -> redir);
        free(*cmd);
        cmd++;
    }
    free(cmd_ptr);
}

void msh_clean(t_msh *msh)
{
    if (msh -> cwd)
		free(msh -> cwd);
    if (msh -> old_wd)
        free(msh -> old_wd);
    if (msh -> envl)
        free_arr((void **) msh -> envl);
    if (msh -> cmd)
        free_cmd(msh -> cmd);
    if (msh -> std_fd)
        restore_stdfd(msh, &msh -> std_fd[0], &msh -> std_fd[1]);
    ft_memset(msh, 0, offsetof(t_msh, exit_code));
}
