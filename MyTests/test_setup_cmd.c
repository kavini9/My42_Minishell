/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_setup_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:17:28 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/06 23:47:05 by wweerasi         ###   ########.fr       */
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

int is_ambi_redir(char **expan)
{
  if (ft_arrlen(expan) > 1 || !**expan )
    return (1);
  return (0);
}

char *remove_quotes(char *q_arg)
{
  int single_q;
  int double_q;
  int len;
  char *arg;

  single_q = 0;
  double_q = 0;
  len = ft_strlen(q_arg);
  arg = q_arg;
  while(len--)
  {
    if (*q_arg == '\'' && !double_q)
    {
        single_q = !single_q;
        ft_memmove(q_arg, q_arg + 1, len + 1);
    }
    else if (*q_arg == '"' && !single_q)
    {
        double_q = !double_q;
        ft_memmove(q_arg, q_arg + 1, len + 1);
    }
    else
        q_arg++;  
  }
  return(arg);
}

void  addto_redir_arr(t_msh *msh, t_token *token, t_cmd *cmd, int *len)
{
  char q_arg;
  char arg;
  
  cmd -> redir = ft_realloc(token -> redir, (*len + 1) * sizeof(t_redir *), (*len + 2) * sizeof(t_redir *));
  if (cmd -> redir)
    exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
  cmd -> redir[*len] = ft_calloc(1, sizeof(t_redir));
  if (token -> redir[len])
    exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
  cmd -> redir[*len] -> type = token -> redir;
  if (token -> redir = REDIR_HDOC && 
  (ft_strchr(token -token, '\'') || ft_strchr(token -token, '"')))
    cmd -> redir[*len] -> ambi_o_hdexp = 1;
  if (token -> expn && !is_ambi_redir(token -> expn))
    q_arg = *(token -> expn);
  else
  {
    q_arg = token -> token;
    cmd -> redir[*len] -> ambi_o_hdexp = 1;
  }
  arg = ft_strdup(remove_quotes(q_arg));
  if (!arg)
    exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC.
  cmd -> redir[*len] -> fname_o_del = arg;
}

void  q_unwrap_append(t_msh *msh, t_cmd *cmd, char *q_arg)
{
  char *arg;
  size_t len;
  
  remove_quotes(q_arg);
  arg = ft_strdup(q_arg);//the q_arg needs to be freed. but do it in a later stage at once with all exp_utils otherwise might loose some the reference to later elements.
  if (!arg)
    exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC.
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
//what happens when a token with redir flag is coming in a array. See if it is avoided in the expansion//HANDLED

void  addto_cmd_arr(t_msh *msh, t_token *token, t_cmd *cmd)
{
  char **exp_arr;
  
  if ((token -> expn))
  {
    exp_arr = token -> expn;
    while (*exp_arr)
    {
      q_unwrap_append(msh, cmd, *exp_arr);//inside this check if redir flag exist and add to two arrays accordingly.
      exp_arr++;
    }
  }
  else
    q_unwrap_append(msh, cmd, token -> token);
}

void  setup_cmd(t_msh *msh, t_token **token, t_cmd **cmd)
{
  char **exp_arr;
  t_token *token_iter;
  int redir_count;

  while (*token)
  {
    token_iter = *token;
    redir_count = 0;
    while ((*token_iter).token)
    {
      if (!(*token_iter).redir)
        addto_cmd_arr(msh, token_iter, *cmd);
      else
        addto_redir_arr(msh, token_iter, *cmd, &redir_count);
      token_iter++;
    }
    cmd++;
    token++;
  }
}