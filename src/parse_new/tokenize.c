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

void	*ft_realloc(void *ptr, size_t size_prev, size_t size_new)
{
	void	*ptr_new;

	if (!ptr)
		return (malloc(size_new));
	if (!size_new)
	{
		free(ptr);
		return (NULL);
	}
	ptr_new = malloc(size_new);
	if (!ptr_new)
		return (NULL);//should I set errno to ENOMEM
	if (size_prev > 0)
	{
		if (size_prev > size_new)
			ft_memcpy(ptr_new, ptr, size_new);
		else
			ft_memcpy(ptr_new, ptr, size_prev);
	}
	free(ptr);
	return (ptr_new);
}

void skip_whitespaces(char **str)
{
    while (ft_strchr(" \t\n\r\f\v", **str) && !**str)
        *str++;
}

char *extract_token(t_msh *msh, t_parse *aux, char *seg)
{
    t_token **token;
    int     tok_len;
    int     tok_arr_size;

    tok_arr_size = 0;
    token = aux -> token;
    while (*seg)
    {
        *token = ft_realloc(*token, tok_arr_size, ++tok_arr_size);
        if (!*token)
            exit(printf("Malloc Error token array\n"));
        ft_memset(*token + tok_arr_size, 0, sizeof(t_token));
        tok_len = get_token_len(token, seg, 0);
        (*token + tok_arr_size) -> token = ft_substr(seg, 0, tok_len);
        if (!(*token + tok_arr_size) -> token)
            exit(printf("Malloc Error token %i\n", tok_arr_size));
        seg += tok_len;
        skip_whitespaces(&seg);
    }
}

void	seg_tokenize(t_msh *msh, t_parse *aux)
{
	char    **seg;
    char    *tok;
    
    seg = aux -> seg;
    while (seg)
    {
        extract_token(msh, aux, *seg);
        seg++;
    } 
    
}