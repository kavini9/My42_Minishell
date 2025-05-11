/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:57:47 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/11 20:51:34 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int set_redir_type(t_token *token, char *seg)
{
    if (*seg == '<' && *(seg + 1) == '<')
        token -> redir = REDIR_HDOC;
    else if (*seg == '>' && *(seg + 1) == '>')
        token -> redir = REDIR_APPEN;
    else if (*seg == '<')
        token -> redir = REDIR_INP;
    else if (*seg == '>')
        token -> redir = REDIR_OUTP;
    else
        return (0);
    return (1);
}

int get_token_len(t_token *token, char *seg, int tok_len)
{
    int redir_flg;
    int quote_flg;
    int is_white;

    redir_flg = 0;
    quote_flg = 0;
    while (*seg)
    {
        is_white = ft_strchr(" \t\n\r\f\v", *seg);
        if ((*seg == '\'' || *seg == '"') && !quote_flg)
            quote_flg = (int) *seg;
        else if ((*seg == '\'' || *seg == '"') && quote_flg == (int) *seg)
            quote_flg = 0;
        if (redir_flg && !is_white)
            redir_flg = 0;
        if ((*seg == '<' || *seg == '>') && !quote_flg && !redir_flg && tok_len)
            break;
        if ((*seg == '<' || *seg == '>') && !quote_flg && !redir_flg)
            redir_flg = set_redir_type(token, seg);
        if (is_white && !quote_flg && !redir_flg)
            break;
        tok_len++;
        seg++;
    }
    return (tok_len);
}

char *extract_token(t_msh *msh, t_parse *aux, char *seg)
{
    t_token **token;
    int     tok_len;
    
    token = aux -> token;
    while (*seg)
    {
        if (!*token)
            *token = ft_calloc(1, sizeof(t_token));
        else
            *token = ft_realloc(*token, 
        tok_len = get_token_len(token, seg, 0);
        

    }
}

void	seg_tokenize(t_msh *msh, t_parse *aux)
{
	char    **seg;
    char    *tok;
    
    seg = aux -> seg;
    while (*seg)
    {
        extract_token(msh, aux, *seg);

    } 
    
}