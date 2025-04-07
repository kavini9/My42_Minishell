/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:47:01 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/07 04:46:01 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	dup_io(t_msh *msh, int rd_fd, int wr_fd)
{
	if (dup2(rd_fd, STDIN_FILENO) == -1)
		exit(printf("error\n"));
	if (dup2(wr_fd, STDOUT_FILENO) == -1)
        exit(printf("error\n"));
}

// void    redirect_io(t_msh *msh, t_redir *redir, int rd_fd, int wr_fd)
// {
    
// }