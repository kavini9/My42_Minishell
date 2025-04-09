/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:47:01 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/09 22:47:50 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	dup_io(t_msh *msh, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		close (oldfd);
		return  (-1);
	}
	close(oldfd);
	return (oldfd);
}

int	open_file(t_msh *msh, t_redir_type type, char *fname)
{
	int fd;
	
	fd = -1;
	if (type == REDIR_INP)
		fd = open(fname, O_RDONLY);
	else if (type == REDIR_OUTP)
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd = -1)
		exit("file open error\n");
	return (fd);
}

void	redirect_pipe(t_msh *msh, int rd_fd, int wr_fd)
{
	int ret;
	
	ret = 0;
	if (rd_fd != -1)
		ret = dup_io(msh, rd_fd, STDIN_FILENO);
	if (ret == -1)
		close(wr_fd);
	if (ret >= 0 && wr_fd != -1)
		ret = dup_io(msh, wr_fd, STDOUT_FILENO);
	if (ret)
	
}

void	close_all_hdocfd(int *hdocfd_l)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (hdocfd_l[i] != 0)
			close(hdocfd_l[i]);
			i++;
	}	
}

void    redirect_io(t_msh *msh, t_cmd *cmd, int fd, int i)
{
	t_redir *redir;
	
	redir = cmd -> redir;
	while (redir) // check if redir -> fname exist. ex: <$NONEXIST_FILE. should give ambiguous redirection 
	{
		if (redir -> type != REDIR_HDOC)
			fd = open_file(msh, redir -> type, redir -> fname_o_del);
		else
		{
			fd = *(msh ->  hdocfd_l + cmd -> hdoc_st_pos + i);
			*(msh -> hdocfd_l + cmd -> hdoc_st_pos + i) = -1;
			i++;
		}
		//if (fd == -1)
			//send_help();TODO: ERROR handling
		if (redir -> type == REDIR_INP || redir -> type == REDIR_HDOC)
				fd = dup_io(msh, fd, STDIN_FILENO);
		else
				fd = dup_io(msh, fd, STDOUT_FILENO);
		//if (fd == -1)
			//send_help(); TODO: ERROR handling	
	}
	close_all_hdocfd(msh -> hdocfd_l);
}

//to change the increasing pointer exceed the array limit, insted of setting a int pointr
//for hdoc_fd n cmd we can assign just a number. if this number exceed 
REDIR_HDOC,
	REDIR_INP,
	REDIR_OUTP,
	REDIR_APPEN,