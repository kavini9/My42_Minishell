/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:28 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/13 00:23:19 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void error_log(int err_type, char *param)
{
    int err_no;

    if (err_type == ERR_SYS_FUNC)
    {
        err_no = errno;
        printf_fd(STDERR_FILENO, "minishell: %s: %s\n", param, strerror(err_no));
    }
    else if (err_type == ERR_MALLOC)
        printf_fd(STDERR_FILENO, "minishell: memory allocation fail\n");      
        
}

void msh_error(t_msh *msh, t_do_err opt_exitc, t_err_type err_type, char *param)
{
    int exit_code = opt_exitc & 0xFF;
    int opt = (opt_exitc >> 8) & 0xFF;
      
    if (opt & LOG)
        error_log(err_type, param);
    if (opt & CLEAN)
        msh_clean(msh);
    if (opt & EXIT)
        exit(msh -> exit_code);
}


void msh_builtin_error(t_msh *msh, )