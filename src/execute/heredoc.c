/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:42:50 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/07 03:43:16 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    get_here_doc(t_msh *msh, t_redir *redir, int *hdoc_fd)
{
    int hd_pfd[2];
    char *line;

    if (pipe(hd_pfd) == -1)
        exit(print("pipe did not open\n"));//TODO: ERROR. See what is need to be freed.
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, redir -> fname_o_del))
            break;
        ft_puendl_fd(line, hd_pfd[1]);
        free(line);
    }
    if (!line)
        exit(printf(""));
    free(line);
    close(hd_pfd[1]);
    *hdoc_fd = hd_pfd[0];
}

void    here_doc(t_msh *msh, t_cmd *cmd, int *hdocfd_l, int i)
{
    t_redir *redir;

    while(cmd)
    {
        redir = cmd -> redir;
        cmd -> hdocfd = hdocfd_l;
        while(redir)
        {
            if (redir -> type == REDIR_HDOC)
            {
                get_heredoc_inp(msh, redir , hdocfd_l);
                if (++i < 16)
                    hdocfd_l++;
            }
            redir = redir -> next;
        }
        cmd = cmd -> next;
    }
}