/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:47:01 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 09:26:55 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dup_io(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		close (oldfd);
		return (-1);
	}
	if (oldfd != newfd)
		close(oldfd);
	return (oldfd);
}

int	open_file_gethdfd(t_msh *msh, t_cmd *cmd, t_redir *redir, int *i)
{
	int				fd;
	char			*fname;
	t_redir_type	type;

	fd = -1;
	fname = redir -> fname_o_del;
	type = redir-> type;
	if (type == REDIR_HDOC)
	{
		fd = *(msh -> hdocfd_l + cmd -> hdoc_st_pos + *i);
		*(msh -> hdocfd_l + cmd -> hdoc_st_pos + *i) = -1;
		(*i)++;
	}
	else if (type == REDIR_INP)
		fd = open(fname, O_RDONLY);
	else if (type == REDIR_OUTP)
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

void	redirect_pipe(t_msh *msh, int rd_fd, int wr_fd)
{
	int	dup_ret;

	dup_ret = 0;
	if (rd_fd != -1)
		dup_ret = dup_io(rd_fd, STDIN_FILENO);
	if (dup_ret < 0)
		close(wr_fd);
	else if (wr_fd != -1)
		dup_ret = dup_io(wr_fd, STDOUT_FILENO);
	if (dup_ret < 0)
		msh_error(msh, (ERRNO | LOG | CLEAN | EXIT) << 8 | 1, ERR_SYSFUNC,
			"dup");
}

void	redirect_io(t_msh *msh, t_cmd *cmd, int fd, int i)
{
	int		dup_ret;
	t_redir	**redir;

	dup_ret = 0;
	redir = cmd -> redir;
	while (redir && *redir)
	{
		if ((*redir)-> type != REDIR_HDOC && (*redir)-> ambi_o_hdexp)
			return (msh_error(msh, (ERRNO | LOG) << 8 | 1, ERR_AMBI_REDIR,
					(*redir)-> fname_o_del));
		else
			fd = open_file_gethdfd(msh, cmd, *redir, &i);
		if (fd == -1)
			return (msh_error(msh, (ERRNO | LOG) << 8 | 1, ERR_SYSFUNC,
					(*redir)-> fname_o_del));
		if ((*redir)-> type == REDIR_INP || (*redir)-> type == REDIR_HDOC)
			dup_ret = dup_io(fd, STDIN_FILENO);
		else
			dup_ret = dup_io(fd, STDOUT_FILENO);
		if (dup_ret < 0)
			return (msh_error(msh, (ERRNO | LOG) << 8 | 1, ERR_DUP,
					ft_itoa(fd)));
		redir++;
	}
	close_all_hdocfd(msh -> hdocfd_l);
}
