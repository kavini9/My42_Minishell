/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execif_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:05:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/10 17:55:05 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

execif_builtin(t_msh *msh, char **cmd)
{
    if (ft_strcmp(*cmd, "echo"))
        return(builtin_echo(msh, cmd));
    else if (ft_strcmp(*cmd, "cd"))
        return(builtin_cd(msh, cmd));
    else if (ft_strcmp(*cmd, "pwd"))
        return(builtin_pwd(msh));
    else if (ft_strcmp(*cmd, "export"))
        return(builtin_export(msh, cmd));
    else if (ft_strcmp(*cmd, "unset"))
        return(builtin_unset(msh, cmd));
    else if (ft_strcmp(*cmd, "env"))
        return(builtin_env(msh, cmd));
    else if (ft_strcmp(*cmd, "exit"))
        return(builtin_exit(msh, cmd));
}
