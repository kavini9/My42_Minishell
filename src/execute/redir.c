/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:47:01 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/08 21:46:16 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	dup_io(t_msh *msh, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		exit(printf("error\n"));//TODO
	close(oldfd);
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

void    redirect_io(t_msh *msh, t_cmd *cmd, int rd_fd, int wr_fd)
{
	int i;
	int fd;
	t_redir *redir;
	
	i = 0;
	fd = -1;
	redir = cmd -> redir;
    if (rd_fd != -1)
		dup_io(msh, rd_fd, STDIN_FILENO);
	if (wr_fd != -1)
		dup_io(msh, wr_fd, STDOUT_FILENO);
	while (redir) // check if redir -> fname exist. ex: <$NONEXIST_FILE. should give ambiguous redirection 
	{
		if (redir -> type != REDIR_HDOC)
			fd = open_file(msh, redir -> type, redir -> fname_o_del);
		else
		{
			fd = *(msh ->  hdocfd_l + cmd -> hdoc_st_pos + i);
			i++;
		}
		if (redir -> type == REDIR_INP || redir -> type == REDIR_HDOC)
				dup_io(msh, fd, STDIN_FILENO);
		else
				dup_io(msh, fd, STDOUT_FILENO);		
	}
}

//to change the increasing pointer exceed the array limit, insted of setting a int pointr
//for hdoc_fd n cmd we can assign just a number. if this number exceed 
REDIR_HDOC,
	REDIR_INP,
	REDIR_OUTP,
	REDIR_APPEN,