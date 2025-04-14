/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:28 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/14 23:41:02 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void error_log(int err_msg, char *param, int err_no)
{
    if (param && err_no)
        fd_printf(STDERR_FILENO, err_msg, param, strerror(err_no));
    else if (param && !err_no)
        fd_printf(STDERR_FILENO, err_msg, param);
    else if (!param && err_no)
        fd_printf(STDERR_FILENO, err_msg, strerror(err_no));
    else
        fd_printf(STDERR_FILENO, err_msg);
}

void msh_error(t_msh *msh, t_do_err opt_exc, char *err_msg, char *param)
{
    int opt;
    int errsv;

    opt = (opt_exc >> 8) & 0xFF;
    errsv = 0;
    msh -> exit_code = opt_exc & 0xFF;
    if (opt & ERRNO)
        errsv = errno;
    if (opt & LOG)
        error_log(err_msg, param, errsv);
    if (opt & CLEAN)
        msh_clean(msh);
    if (opt & EXIT)
        exit(msh -> exit_code);
}