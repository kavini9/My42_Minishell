/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:24:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/04 15:00:00 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	dup_io(t_pipex *pipex, int rd_fd, int wr_fd)
{ 
	if (dup2(rd_fd, STDIN_FILENO) == -1)
		pipex_sys_error("dup2: ", ft_itoa(rd_fd), pipex);
	if (dup2(wr_fd, STDOUT_FILENO) == -1)
		pipex_sys_error("dup2: ", ft_itoa(wr_fd), pipex);
}

void	open_file(int i, int *fd, char *file, t_pipex *pipex)
{
	if (i == 0)
		*fd = open(file, O_RDONLY);
	else if (pipex -> heredoc == 1)
		*fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
		pipex_sys_error("open: ", file, pipex);
}

void	redirect_io(int i, t_pipex *pipex)
{
	if (i == 0)
	{
		open_file(i, &(pipex -> infd), pipex -> av[1], pipex);
		dup_io(pipex, pipex -> infd, pipex -> pfds[1]);
		if (pipex -> heredoc == 1)
			unlink("here_doc");
		close(pipex -> infd);
	}
	else if (i == pipex -> cmd_count - 1)
	{
		open_file(i, &(pipex -> outfd), pipex -> av[pipex -> ac - 1], pipex);
		dup_io(pipex, pipex -> pfds[2 * (i - 1)], pipex -> outfd);
		close(pipex -> outfd);
	}
	else
	{
		i *= 2;
		dup_io(pipex, pipex -> pfds[i - 2], pipex -> pfds[i + 1]);
	}
	close_pfds(pipex);
}

void	wait_child(int i, pid_t pid, t_pipex *pipex)
{
	int	status;

	while (i--)
	{
		if (wait(&status) == pid)
		{
			if (WIFEXITED(status))
				pipex -> status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) && WTERMSIG(status))
				pipex -> status = 128 + WTERMSIG(status);
		}
	}
}

void	ft_pipex(t_pipex *pipex)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < pipex -> cmd_count)
	{
		pid = fork();
		if (pid < 0)
		{
			wait_child(i, pid, pipex);
			pipex_sys_error("fork: ", ft_itoa(i), pipex);
		}
		else if (pid == 0)
		{
			redirect_io(i, pipex);
			execute_cmd(i, pipex);
		}
		i++;
	}
	pipex_clean(pipex);
	wait_child(i, pid, pipex);
}
