/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:02:37 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/07 20:28:53 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	 check_quotes(char *start, char *end)
{
	int	single_quote;
	int	double_quote;

    single_quote = 0;
	double_quote = 0;
    while (*start && start != end)
	{
		if (*start == '\'' && !double_quote)
			single_quote = !single_quote * ((int) *start) ; 
		else if (*start == '"' && !single_quote)
			double_quote = !double_quote * ((int) *start); 
		start++;
	}
	if (single_quote)
	    return (single_quote);
    if (double_quote)
	    return (double_quote);
    return (0);
}

void skip_whitespaces(char **str)
{
    while (**str && ft_strchr(" \t\n\r\f\v", **str))
        (*str)++;
}

int redir_skip(char *seg)
{
    int skip;

    skip = 0;
    while(*seg && ft_strchr("< \t\n\r\f\v>", *seg))
    {
        skip++;
        seg++;
    }
    return (skip);
}

int is_ambi_redir(char **expan)
{
  if (ft_arrlen((void **) expan) > 1 || !**expan )
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
//auxiliary. delete later

void print_segments(char **seg)
{
    printf("pirnting segments\n");
    while (*seg)
    {
        printf("[%s]\n", *seg);
        seg++;
    }
}

void print_tokens(t_token **token)
{
    t_token *tok_arr;

    while (*token)
    {
        printf("pirnting tokens for each segment\n");
        tok_arr = *token;
        while(tok_arr -> token)
        {
            printf("[%s]        redir: %i\n", tok_arr -> token, (int) tok_arr -> redir );
            tok_arr++;
        }
        token++;
    }
}

void print_expand_arrays(t_token **token)
{
    t_token *tok_arr;
    char **expn;

    while (*token)
    {
        printf("pirnting expn for each segment\n");
        tok_arr = *token;
        while(tok_arr -> token)
        {
            printf("token: %s\n", tok_arr -> token);
            expn = tok_arr -> expn;
            while(expn && *expn)
            {
                printf("[%s]\n", *expn);
                expn++;
            }
            tok_arr++;
        }
        token++;
    }
}

void print_cmd_members(t_cmd **cmd)
{
    char **cmd_arr;
    t_redir **redir_arr;
    int i;

    while (*cmd)
    {
        printf("printing cmd_memebers for each cmd segment\n");
        cmd_arr = (*cmd) -> cmd;
        i = 0;
        while (cmd_arr && *cmd_arr)
        {
            printf("cmd %i: [%s]\n", i++, *cmd_arr);
            cmd_arr++;
        }
        redir_arr = (*cmd) -> redir;
        i = 0;
        while (redir_arr && *redir_arr)
        {
            printf("redir %i:   type: %i    flag: %i    [%s]\n", i++, (*redir_arr) -> type, (*redir_arr) -> ambi_o_hdexp, (*redir_arr) -> fname_o_del);
            redir_arr++;
        }
        cmd++;
    }
}