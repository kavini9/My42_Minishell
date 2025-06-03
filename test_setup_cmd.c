/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_setup_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:28 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/03 20:35:32 by wweerasi         ###   ########.fr       */
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

void setup_cmd(t_msh *msh, t_token **token)
{
  char **exp_arr;
  char **cmd;

  init_cmd_struct(msh, msh -> cmd_count);
  cmd = msh -> cmd;
  while (*token)
  {
    while ((**token).token)
    {
      if ((**token).expn)
      {
        exp_arr = (**token).expn;
        while (*exp_arr)
        {
          quote_remove(*exp_arr);
          add_to_cmd(t_msh *msh, *cmd, exp_arr);//inside this check if redir flag exist and and to two arrays accordingly.
           exp_arr++;
        }
      }
      else
        quote_remove((**token).token);


    }
  }
}

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