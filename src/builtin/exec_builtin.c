/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:05:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/20 06:02:02 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int is_builtin(char **cmd)
{
    if (cmd && *cmd && (ft_strcmp(*cmd, "echo")
        || ft_strcmp(*cmd, "cd")
        || ft_strcmp(*cmd, "pwd")
        || ft_strcmp(*cmd, "export")
        || ft_strcmp(*cmd, "unset")
        || ft_strcmp(*cmd, "env")
        || ft_strcmp(*cmd, "exit")))
        return (1);
    return (0);
}

void exec_builtin(t_msh *msh, char **cmd)
{        
    if (ft_strcmp(*cmd, "echo"))
        builtin_echo(msh, cmd);
    else if (ft_strcmp(*cmd, "cd"))
        builtin_cd(msh, cmd);
    else if (ft_strcmp(*cmd, "pwd"))
        builtin_pwd(msh);
    else if (ft_strcmp(*cmd, "export"))
        builtin_export(msh, cmd);
    else if (ft_strcmp(*cmd, "unset"))
        builtin_unset(msh, cmd);
    else if (ft_strcmp(*cmd, "env"))
        builtin_env(msh, cmd);
    else if (ft_strcmp(*cmd, "exit"))
        builtin_exit(msh, cmd);
    else
        return(0);
    return (1);
}

void execin_shell(t_msh *msh, char **cmd)
{
    int std_fd[2];

    memset(std_fd, -1, 2 * sizeof(int));
    std_fd[0] = dup(STDIN_FILENO);
    std_fd[1] = dup(STDOUT_FILENO);
    if (std_fd[0] == -1 || std_fd[1] == -1)
    {
        if (std_fd[0] != -1)
            close(std_fd[0]);
        if (std_fd[1] != -1)
            close(std_fd[1]);
        msh_error(msh, (ERRNO|LOG|CLEAN|EXIT) << 8 | 1, ERR_SYSFUNC, "dup");
    }
    redirect_io(msh, cmd, -1, 0);//if this fails we might also loose std_fds.
    if (msh -> exit_code == 0)
        exec_builtin(msh, cmd);
    //reset std_in and std_out
}   
//Exit codes are set in every end point of the builtins. When encountered an error msh_error may set the exit code and might exit if required.