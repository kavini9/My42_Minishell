/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_setup_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:28 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/06 14:28:16 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int print_cmd(t_cmd *cmd)
{
  if(cmd)
  {
    printf("cmd : %s\n", *cmd->cmd);
    printf("err note \n");
    printf("cmd path : %s\n", cmd->err_note.cmd_path);
    printf("strerr : %s\n", cmd->err_note.strerr);
    t_redir *temp = cmd->redir;
    while(temp)
    {
      printf("expan : %d\n", cmd->redir->expan);
      printf("filename : %s\n", cmd->redir->fname_o_del);
      printf("type : %d\n", cmd->redir->type);
      temp = temp->next;
    }
    printf("hdoc st pos : %d\n", cmd->hdoc_st_pos);
    return (0);
  }
  return (0);  
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

void  set_redir_arr(t_msh *msh, t_cmd *cmd, char *q_arg, int redir)
{
  (void)msh;
  (void)q_arg;
  (void)redir;
  print_cmd(cmd);
}

void  add_to_cmd_struct(t_msh *msh, t_cmd *cmd, char *q_arg, int redir)
{
  char *arg;
  size_t len;
  
  //remove_quotes(q_arg);
  arg = ft_strdup(q_arg);//the q_arg needs to be freed. but do it in a later stage at once with all exp_utils otherwise might loose some the reference to later elements.
  if (!arg)
    exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC.
  if (!redir)
  {
    if (cmd -> cmd)
      len = ft_arrlen((void *) cmd -> cmd);
    else
      len = 0;
    cmd -> cmd = ft_realloc(cmd -> cmd, (len + 1) * sizeof(char *), (len + 2) * sizeof(char *));//if pointer is NULL, then sizeprev is not used in ft_realloc
    if (cmd -> cmd)
      exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
    cmd -> cmd[len + 1] = arg;
    cmd -> cmd[len + 2] = NULL;
  }
  else
    set_redir_arr(msh, cmd, q_arg, redir);
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
