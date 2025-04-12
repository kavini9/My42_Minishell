/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execif_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:05:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/12 20:40:14 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

execif_builtin(t_msh *msh, char **cmd)
{
    if (ft_strcmp(*cmd, "echo"))
        msh -> exit_code = builtin_echo(msh, cmd);
    else if (ft_strcmp(*cmd, "cd"))
        msh -> exit_code = builtin_cd(msh, cmd);
    else if (ft_strcmp(*cmd, "pwd"))
        msh -> exit_code = builtin_pwd(msh);
    else if (ft_strcmp(*cmd, "export"))
        msh -> exit_code = builtin_export(msh, cmd);
    else if (ft_strcmp(*cmd, "unset"))
        msh -> exit_code = builtin_unset(msh, cmd);
    else if (ft_strcmp(*cmd, "env"))
        msh -> exit_code = builtin_env(msh, cmd);
    else if (ft_strcmp(*cmd, "exit"))
        msh -> exit_code = builtin_exit(msh, cmd);
    else
        return(0);
    return (1);
}

// Maybe we'll set this exit code in builtin function itself rather than sending here and setting ot here.