/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:09:42 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/17 20:24:12 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    builtin_cd(t_msh *msh, char **cmd)
{
    if (cmd[2])
        msh_error("minishell: cd: too many arguments\n");//TODO: should not exit minishell but prints error message.
    else if (!cmd[1] || ft_strcmp(cmd[1], "~"))
        cd_home_dir(msh);
    else if (cmd[1][0] == '~')
        cd_tilde(msh);
    else if (ft_strcmp(cmd[1], "--")) //optional. might have to do something with parsing
        cd_dir_literal(msh);
    else if (ft_strcmp(cmd[1], "-"))
        cd_old_dir(msh);
    else
        cd_path(msh);
}
