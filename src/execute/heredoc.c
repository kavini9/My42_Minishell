/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:42:50 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 19:50:19 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_child(t_msh *msh, t_redir *redir, int *pipefd)
{
	char	*line;
	int		i;

	i = 1;
	sig_heredoc();
	close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT || !line)
			break ;
		if (!ft_strcmp(line, redir->fname_o_del))
			break ;
		ft_putendl_fd(line, pipefd[1]);
		free(line);
		i++;
	}
	if (!line && !g_sig)
		printf_fd(2, "minishell: warning: here-document at line %i delimited"
			" by end-of-file (wanted `%s')\n", i, redir->fname_o_del);
	free(line);
	close(pipefd[1]);
	msh_clean(msh);
	exit(g_sig);
}

static void	hd_sigint_action(t_msh *msh, int *pipefd, int *hdoc_fd)
{
	msh -> exit_code = 130;
	write(STDERR_FILENO, "\n", 1);
	close(pipefd[0]);
	*hdoc_fd = -1;
}

void	get_here_doc(t_msh *msh, t_redir *redir, int *hdoc_fd)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (msh_error(msh, (ERRNO | LOG | CLEAN) << 8 | 1, ERR_SYSFUNC,
				"pipe"));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (msh_error(msh, (ERRNO | LOG | CLEAN) << 8 | 1, ERR_SYSFUNC,
				"fork"));
	if (pid == 0)
		heredoc_child(msh, redir, pipefd);
	waitpid(pid, &status, 0);
	init_sig();
	close(pipefd[1]);
	if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
		return (hd_sigint_action(msh, pipefd, hdoc_fd));
	*hdoc_fd = pipefd[0];
}

static void	heredoc_limiter(t_msh *msh, t_cmd **cmd)
{
	int		i;
	t_redir	**redir;

	i = 0;
	while (*cmd)
	{
		redir = (*cmd)->redir;
		while (redir && *redir)
		{
			if ((*redir)->type == REDIR_HDOC)
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
	while (*cmd && msh->exit_code == 0)
	{
		redir = (*cmd)->redir;
		(*cmd)->hdoc_st_pos = i;
		while (redir && *redir)
		{
			if ((*redir)->type == REDIR_HDOC)
			{
				get_here_doc(msh, *redir, hdocfd_l + i);
				if (msh->exit_code == 130)
					return ;
				i++;
			}
			redir++;
		}
		cmd++;
	}
}
