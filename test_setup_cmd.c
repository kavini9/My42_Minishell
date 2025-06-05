/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_setup_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:28 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/05 17:37:39 by wweerasi         ###   ########.fr       */
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

void  add_to_cmd_struct(t_msh *msh, t_cmd *cmd, char *q_arg, int redir)
{
  char *arg;
  size_t len;
  
  
  remove_quotes(q_arg);
  arg = ft_strdup(q_arg);//the q_arg needs to be freed. but do it in a later stage at once with all exp_utils otherwise might loose some the reference to later elements.
  if (!arg)
    exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC.
  if (!redir)
  {
    if (cmd -> cmd)
      len = ft_arrlen((void *) cmd -> cmd);
    else
      len = 0;
    cmd -> cmd = ft_realloc(cmd -> cmd, (len + 1) * sizeof(char *), (len + 2) * sizeof(char *));
    if (cmd -> cmd)
      exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
    cmd -> cmd[len + 1] = arg;
  }
  else
    set_redir_arr()
}
//what happens when a token with redir flag is coming in a array. See if it is avoided in the expansion//HANDLED

void  setup_cmd(t_msh *msh, t_token **token, t_cmd **cmd)
{
  char **exp_arr;
  t_token *token_iter;

  while (*token)
  {
    token_iter = *token;
    while ((*token_iter).token)
    {
      if ((*token_iter).expn)
      {
        exp_arr = (*token_iter).expn;
        while (*exp_arr)
        {
          add_to_cmd_struct(msh, *cmd, *exp_arr, (*token_iter).redir);//inside this check if redir flag exist and and to two arrays accordingly.
           exp_arr++;
        }
      }
      else
        add_to_cmd_struct(msh, *cmd, (*token_iter).token, (*token_iter).redir);
      token_iter++;
    }
    cmd++;
    token++;
  }
}