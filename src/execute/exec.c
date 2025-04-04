/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:29:15 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/05 00:03:10 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    redirect_io()
{
     
}

void here_doc(t_msh *msh)
{
    
}

void    exec_pipex(t_msh *msh)
{
    int i;
    int pipe_fd[2];
    int prev_rd_fd;
    pid_t pid;
    
    i = 0;
    prev_rd_fd = -1;
    while (i < msh -> cmd_count)
        if (i < msh -> cmd_count - 1)
            pipe(pipe_fd);
        pid = fork();
        if (pid == 0)
        {
            redirect_io(...);
            execute_cmd(...);
        }      
}

void    execin_child(t_msh *msh)
{
    here_doc(msh); 
    if (msh -> cmd_count == 1)
        exec_single(msh);
    else
        exec_pipex(msh);
}
//ls | sort | grep src remember to understand what happens here. does this break the
//pipeline. 


/*
wweerasi@c1r6p3:~/My42/minishell/Repo$ sort <<e1<<e2<<e3<<e4<<e5<<e6<<e7<<e8<<e9<<e10<<e11<<e12<<e13<<e14<<e15<<e16<<e17
bash: maximum here-document count exceeded
*/