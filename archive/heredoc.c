/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:42:50 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 06:02:31 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_here_doc(t_msh *msh, t_redir *redir, int *hdoc_fd)
{
	int		hd_pfd[2];
	char	*line;
	int		i;

	i = 1;
	if (pipe(hd_pfd) == -1)
		return (msh_error(msh, (ERRNO | LOG | CLEAN) << 8 | 1,
				ERR_SYSFUNC, "pipe"));
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, redir -> fname_o_del))
			break ;
		ft_putendl_fd(line, hd_pfd[1]);
		free(line);
		i++;
	}
	if (!line)
		printf_fd(2, WAR_HDEOF, i, redir -> fname_o_del);
	free(line);
	close(hd_pfd[1]);
	*hdoc_fd = hd_pfd[0];
}

static void	heredoc_limiter(t_msh *msh, t_cmd **cmd)
{
	int		i;
	t_redir	**redir;

	i = 0;
	while (*cmd)
	{
		redir = (*cmd)-> redir;
		while (redir && *redir)
		{
			if ((*redir)-> type == REDIR_HDOC)
				i++;
			redir++;
		}
		cmd++;
	}
	if (i > HEREDOC_MAX)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 2, ERR_HDLIM, NULL);
}

void	here_doc(t_msh *msh, t_cmd **cmd, int *hdocfd_l, int i)
{
	t_redir	**redir;

	heredoc_limiter(msh, cmd);
	while (*cmd)
	{
		redir = (*cmd)-> redir;
		(*cmd)-> hdoc_st_pos = i;
		while (redir && *redir)
		{
			if ((*redir)-> type == REDIR_HDOC)
			{
				get_here_doc(msh, *redir, hdocfd_l + i);
				i++;
			}
			redir++;
		}
		cmd++;
	}
}
