/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:29:15 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/07 04:41:11 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

// void	wait_child(t_msh *msh, int i, pid_t pid)
// {
// 	int	status;

// 	while (i--)
// 	{
// 		if (wait(&status) == pid)
// 		{
// 			if (WIFEXITED(status))
// 				pipex -> status = WEXITSTATUS(status);
// 			else if (WIFSIGNALED(status) && WTERMSIG(status))
// 				pipex -> status = 128 + WTERMSIG(status);
// 		}
// 	}
// }

void run_child_proc(t_msh *msh, t_redir *redir, int rd_fd, int wr_fd)
{
    redirect_io(msh, redir, rd_fd, wr_fd);
    execute_cmd(msh);
}

void    set_pipe_chain(int *prev_rd_fd, int *pipe_fd, int cmd_count, int i)
{
    if (*prev_rd_fd != -1)
            close(*prev_rd_fd);
    if (i < cmd_count - 1)
    {
        *prev_rd_fd = pipe_fd[0];//This is why we need prev_rd_fd to be a pointer. this assigned value shouls be updated in calling function
        close(pipe_fd[1]);
    }   
}

void    exec_pipex(t_msh *msh, t_cmd *cmd, int prev_rd_fd, int i)
{
    int pipe_fd[2];
    pid_t pid;
    
    while (i < msh -> cmd_count)
    {
        memset(pipe_fd, -1, sizeof(int));//to avoid trying to redirect the pfd[1] in last command.
        if (i < msh -> cmd_count - 1 && pipe(pipe_fd) < 0)
            exit(printf("write_fail\n"));//TODO: ERROR
        pid = fork();
        if (pid < 0)
            break;//chidren are waited after exiting the loop. make sure you compare cmd cout with i and do proper error handling.
        if (pid == 0)
            run_child_proc(msh, cmd -> redir, prev_rd_fd, pipe_fd[1]);
        else
            set_pipe_chain(&prev_rd_fd, pipe_fd , msh  -> cmd_count, i);
        cmd = cmd -> next;
        i++;//maybe this is not needed for me except to decide when not to create pipe 
    }
    wait_child(i, pid, msh);//see where i am cleaning cmd shit
    if (i < msh -> cmd_count)
        printf("fork fail\n");
    //clean_cmd;
}

void    execin_child(t_msh *msh)
{
    here_doc(msh, msh -> cmd, msh -> hdocfd_l, 0); 
    if (msh -> cmd_count == 1)
        exec_single(msh);
    else
        exec_pipex(msh, msh -> cmd, -1,  0);
}
//ls | sort | grep src remember to understand what happens here. does this break the
//pipeline. 


/*
wweerasi@c1r6p3:~/My42/minishell/Repo$ sort <<e1<<e2<<e3<<e4<<e5<<e6<<e7<<e8<<e9<<e10<<e11<<e12<<e13<<e14<<e15<<e16<<e17
bash: maximum here-document count exceeded
*/