/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execin_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:29:15 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/27 20:16:04 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	wait_child(t_msh *msh, int i, pid_t pid)
{
	int	status;

	while (i--)
	{
		if (wait(&status) == pid)
		{
			if (WIFEXITED(status))
				msh -> exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) && WTERMSIG(status))
				msh -> exit_code = 128 + WTERMSIG(status);
		}
	}
}

void run_child_proc(t_msh *msh, t_cmd *cmd, int rd_fd, int wr_fd)
{
    redirect_pipe(msh, rd_fd, wr_fd);
    redirect_io(msh, cmd, -1, 0);//might have to add a return value for this
    execute_cmd(msh, cmd);
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

void    safe_pipefork_fail(t_msh *msh, int prev_rd_fd, int *pipe_fd , int err_data_pack)
{
    int i;
    int err_type;

    i = err_data_pack >> 8;
    err_type = (signed char)(err_data_pack & 0xFF);
    if (err_type == 1)
        msh_error(msh, (ERRNO|LOG|CLEAN) << 8 | 1, ERR_SYSFUNC, "pipe");
    else if (err_type == -1)
        msh_error(msh, (ERRNO|LOG|CLEAN) << 8 | 1, ERR_SYSFUNC, "fork");
    if (prev_rd_fd != -1)
        close(prev_rd_fd);
    if (i < msh -> cmd_count - 1 && pipe_fd[0] != -1 && pipe_fd[1] != -1)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }  
}

//here_doc(msh, msh -> cmd, msh -> hdocfd_l, 0);// this shouldnt be here but in syntax error determining part.
void    execin_child(t_msh *msh, t_cmd *cmd, int prev_rd_fd, int i)
{
    int pipe_fd[2];
    pid_t pid;
    
    while (i < msh -> cmd_count)
    {
        pid  = 1;
        memset(pipe_fd, -1, 2 * sizeof(int));//to avoid trying to redirect the pfd[1] in last command.
        if (i < msh -> cmd_count - 1 && pipe(pipe_fd) < 0)
            break;
        pid = fork();
        if (pid < 0)
            break;
        if (pid == 0)
            run_child_proc(msh, cmd, prev_rd_fd, pipe_fd[1]);
        else if (msh -> cmd_count > 1)// it won't go in here if the command count is 1.
            set_pipe_chain(&prev_rd_fd, pipe_fd , msh  -> cmd_count, i);
        cmd++;
        i++;//maybe this is not needed for me except to decide when not to create pipe 
    }
    if (i < msh -> cmd_count)
        safe_pipefork_fail(msh, prev_rd_fd, pipe_fd , (i << 8) | (pid & 0xFF));
    if (i > 0)
        wait_child(i, pid, msh);//see where i am cleaning cmd shit
}

// void    execin_child(t_msh *msh)
// {
//     here_doc(msh, msh -> cmd, msh -> hdocfd_l, 0); 
//     // if (msh -> cmd_count == 1)
//     //     exec_single(msh);
//     // else
//     exec_pipex(msh, msh -> cmd, -1,  0);
// }
//ls | sort | grep src remember to understand what happens here. does this break the
//pipeline. 


/*
wweerasi@c1r6p3:~/My42/minishell/Repo$ sort <<e1<<e2<<e3<<e4<<e5<<e6<<e7<<e8<<e9<<e10<<e11<<e12<<e13<<e14<<e15<<e16<<e17
bash: maximum here-document count exceeded
*/