/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:19:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/04 23:23:37 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"


typedef enum e_redirect_type
{
    REDIR_HDOC,
	REDIR_INP,
	REDIR_OUTP,
	REDIR_APPEN,
}   t_redir_type;

typedef struct redir
{
    t_redir_type    type;
    char    *io_str;
    t_redir *next;
}   t_redir;

typedef struct s_cmd
{
    int			cmd_id;
	char		**cmd;
	int			infd;
	int			outfd;
	int			cmd_exit_code;
    t_redir     *redir;
	t_cmd       *next;
} t_cmd;

#endif

