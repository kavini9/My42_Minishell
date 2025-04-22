/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:47:01 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/20 05:52:16 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	dup_io(t_msh *msh, int oldfd, int newfd)//we added a return type to here so when redirecting pipefds if redir rdfd fails you have to close wrfd. so cannont exit minishell from here.
{
	if (dup2(oldfd, newfd) == -1)
	{
		close (oldfd);
		return  (-1);//
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
	return (fd);
}

void	redirect_pipe(t_msh *msh, int rd_fd, int wr_fd)
{
	int dup_ret;
	
	dup_ret = 0;
	if (rd_fd != -1)
		dup_ret = dup_io(msh, rd_fd, STDIN_FILENO);
	if (dup_ret < 0)
		close(wr_fd);
	else if (wr_fd != -1)
		dup_ret = dup_io(msh, wr_fd, STDOUT_FILENO);
	if (dup_ret < 0)
		msh_error(msh, (ERRNO|LOG|CLEAN|EXIT) << 8 | 1, ERR_SYSFUNC, "dup");
}

void	close_all_hdocfd(int *hdocfd_l)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (hdocfd_l[i] != -1)// I had set this value to zero before but it should be -1.so I changed.
		{
			close(hdocfd_l[i]);
			hdocfd_l[i] = -1; // set this to -1 so when we try to clean it later incase  of an error we won't be closing a already closed hdfd.
		}	
		i++;
	}	
}

void    redirect_io(t_msh *msh, t_cmd *cmd, int fd, int i)
{
	int dup_ret;
	t_redir *redir;
	
	dup_ret = 0;
	redir = cmd -> redir;
	while (redir) // check if redir -> fname exist. ex: <$NONEXIST_FILE. should give ambiguous redirection 
	{
		if (redir -> type != REDIR_HDOC)
			fd = open_file(msh, redir -> type, redir -> fname_o_del);// if fname is null as a result of expnsion, it should give ambiguous redirection
		else
		{
			fd = *(msh ->  hdocfd_l + cmd -> hdoc_st_pos + i);
			*(msh -> hdocfd_l + cmd -> hdoc_st_pos + i) = -1;// this is just to make other heredocs to be closed in this child
			i++;
		}
		if (fd == -1)
			return(msh_error(msh, (ERRNO|LOG|CLEAN) << 8 | 1, ERR_SYSFUNC, redir -> fname_o_del));
		else if (redir -> type == REDIR_INP || redir -> type == REDIR_HDOC)
				dup_ret = dup_io(msh, fd, STDIN_FILENO);
		else
				dup_ret = dup_io(msh, fd, STDOUT_FILENO);
		if (dup_ret < 0)
			return(msh_error(msh, (ERRNO|LOG|CLEAN) << 8 | 1, ERR_SYSFUNC_DUP, fd));	//if line count > 25 remove dup_ret and use fd to save it. print error message with dup as parametr.
	}
	close_all_hdocfd(msh -> hdocfd_l);
}

//to change the increasing pointer exceed the array limit, insted of setting a int pointr
//for hdoc_fd n cmd we can assign just a number. if this number exceed.