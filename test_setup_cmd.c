/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_setup_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:28 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/31 18:17:47 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"

void init_cmd_struct(t_msh *msh, int cmd_count)
{
    t_cmd **tmp_cmd;
    
    msh -> cmd = ft_calloc(cmd_count + 1, sizeof(t_cmd *));
    if (!msh -> cmd)
		exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
    tmp_cmd = msh -> cmd;
    while (cmd_count--)
    {
        *tmp_cmd = ft_calloc(1, sizeof(t_cmd));
        if (!*tmp_cmd)
             exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
        tmp_cmd++;
    }
}

init_cmd_struct(msh, msh -> cmd_count);

void setup_cmd(t_msh *msh, t_token **token)
{
  init_cmd_struct(msh, msh -> cmd_count);
  
}