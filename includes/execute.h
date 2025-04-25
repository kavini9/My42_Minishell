/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:19:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/24 17:03:29 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"


/* typedef enum e_redirect_type
{
    REDIR_HDOC,
	REDIR_INP,
	REDIR_OUTP,
	REDIR_APPEN,
}   t_redir_type;

typedef struct redir
{
    t_redir_type    type;//ambiguoous redir. If it comes from expansion and has space then it is ambiguous edirection
    char    *fname_o_del;
    t_redir *next;
}   t_redir;

typedef struct s_errnote
{
	char *cmd_path;
	char *strerr;
}	t_errnote;

typedef struct s_cmd
{
	char		**cmd;
    int			cmd_id;
	int			hdoc_st_pos;
	int			cmd_exit_code;
	t_errnote	err_note;
    t_redir     *redir;
	t_cmd       *next;
} t_cmd;
*/
#endif

