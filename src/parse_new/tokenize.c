/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:57:47 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/06 22:40:57 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void set_qoute_flag(t_parse *aux, char seg)
{
    if ()
}

char *extract_token(t_msh *msh, t_parse *aux, char *seg)
{
    t_token *token;
    char    *tok_st;
    int     tok_len;    
    
    token = aux -> token;
    tok_st = seg;
    tok_len = 0;
    while (*seg)
    {
        if (*seg == '\'' || *seg == '"')
            set_qoute_flag(aux, *seg);
        if (*seg == '<' || *seg == '>' && !token -> quote)
            set_redir_flag(aux, seg);
        if ()
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
        skip_whites(seg);
    } 
    
}