/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:27 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/11 19:07:12 by wweerasi         ###   ########.fr       */
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

void    free_cmd(t_cmd **cmd)
{
    t_redir **redir_arr;
    
    
    while (*cmd)
    {
        if ((*cmd) -> cmd)
            free_arr((void **) (*cmd) -> cmd);
        redir_arr = (*cmd) -> redir;
        while (redir_arr && *redir_arr)
        { 
            free((*redir_arr) -> fname_o_del);
            redir_arr++;
        }
        if ((*cmd) -> redir)
            free_arr((void **) (*cmd) -> redir);
        free(*cmd);
        //ft_memset(cmd, 0, sizeof(t_cmd));
        cmd++;
    }
}

void restore_stdfd(t_msh *msh, int *std_fd)
{
    if(dup2(std_fd[0], STDIN_FILENO) == -1 || dup2(std_fd[1], STDOUT_FILENO) == -1)
        msh_error(msh, (ERRNO|LOG) << 8 | 1, ERR_SYSFUNC, "dup");// is this necessary here
    if (std_fd[0] != -1)
        close(std_fd[0]);
    if (std_fd[1] != -1)
        close(std_fd[1]);
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
        restore_stdfd(msh, msh -> std_fd);
    ft_memset(msh, 0, offsetof(t_msh, exit_code));
}
