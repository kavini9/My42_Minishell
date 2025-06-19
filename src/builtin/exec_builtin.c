/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:05:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/19 15:52:18 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char **cmd)
{
	if (cmd && *cmd && (!ft_strcmp(*cmd, "cd")
			|| !ft_strcmp(*cmd, "echo")
			|| !ft_strcmp(*cmd, "env")
			|| !ft_strcmp(*cmd, "exit")
			|| !ft_strcmp(*cmd, "export")
			|| !ft_strcmp(*cmd, "pwd")
			|| !ft_strcmp(*cmd, "unset")))
		return (1);
	return (0);
}

int	exec_builtin(t_msh *msh, char **cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(*cmd, "cd"))
		builtin_cd(msh, cmd);
	else if (!ft_strcmp(*cmd, "echo"))
		builtin_echo(msh, cmd);
	else if (!ft_strcmp(*cmd, "env"))
		builtin_env(msh);
	else if (!ft_strcmp(*cmd, "exit"))
		builtin_exit(msh, cmd);
	else if (!ft_strcmp(*cmd, "export"))
		builtin_export(msh, cmd);
	else if (!ft_strcmp(*cmd, "pwd"))
		builtin_pwd(msh);
	else if (!ft_strcmp(*cmd, "unset"))
		builtin_unset(msh, cmd);
	else
		return (0);
	return (1);
}

void	restore_stdfd(t_msh *msh, int *fd_0, int *fd_1)
{
	if (*fd_0 != -1 && dup2(*fd_0, STDIN_FILENO) == -1)
		msh_error(msh, (ERRNO | LOG | CLEAN | EXIT) << 8 | 1, ERR_DUP,
			ft_itoa(*fd_0));
	if (*fd_0 != -1)
		close(*fd_0);
	*fd_0 = -1;
	if (*fd_1 != -1 && dup2(*fd_1, STDOUT_FILENO) == -1)
		msh_error(msh, (ERRNO | LOG | CLEAN | EXIT) << 8 | 1, ERR_DUP,
			ft_itoa(*fd_1));
	if (*fd_1 != -1)
		close(*fd_1);
	*fd_1 = -1;
}

void	execin_shell(t_msh *msh, t_cmd *cmd)
{
	int	std_fd[2];

	memset(std_fd, -1, 2 * sizeof(int));
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (std_fd[0] == -1 || std_fd[1] == -1)
	{
		if (std_fd[0] != -1)
			close(std_fd[0]);
		if (std_fd[1] != -1)
			close(std_fd[1]);
		msh_error(msh, (ERRNO | LOG | CLEAN | EXIT) << 8 | 1, ERR_SYSFUNC,
			"dup");
	}
	msh -> std_fd = std_fd;
	redirect_io(msh, cmd, -1, 0);
	if (msh -> exit_code == 0)
		exec_builtin(msh, cmd -> cmd);
	msh -> std_fd = NULL;
	restore_stdfd(msh, &std_fd[0], &std_fd[1]);
}
