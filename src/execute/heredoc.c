/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 03:42:50 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/16 05:48:35 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    get_here_doc(t_msh *msh, t_redir *redir, int *hdoc_fd)
{
    int hd_pfd[2];
    char *line;

    if (pipe(hd_pfd) == -1)
        return(msh_error(msh, (ERRNO|LOG|CLEAN) << 8 | 1, ERR_SYSFUNC, "pipe"));//TODO: ERROR. See what is need to be freed.
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

//TODO: expansion for heredoc

void    here_doc(t_msh *msh, t_cmd *cmd, int *hdocfd_l, int i)
{
    t_redir *redir;

    while(cmd)
    {
        redir = cmd -> redir;
        cmd -> hdoc_st_pos = i;
        while(redir)
        {
            if (redir -> type == REDIR_HDOC)
            {
                get_heredoc_inp(msh, redir , hdocfd_l);
                i++;
            }
            redir = redir -> next;
        }
        cmd = cmd -> next;
    }
}