/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:57:47 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 04:08:45 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_redir_type(t_token *token, char *seg)
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

int	get_token_len(char *seg, t_token *token, int tok_len, int is_white)
{
	int	redir_flg;
	int	quote_flg;

	redir_flg = 0;
	quote_flg = 0;
	while (*seg)
	{
		is_white = (ft_strchr(" \t\n\r\f\v", *seg) != NULL);
		if ((*seg == '\'' || *seg == '"') && !quote_flg)
			quote_flg = (int) *seg;
		else if ((*seg == '\'' || *seg == '"') && quote_flg == (int) *seg)
			quote_flg = 0;
		if (redir_flg && !is_white && !(*seg == '<' || *seg == '>'))
			redir_flg = 0;
		else if ((*seg == '<' || *seg == '>') && !quote_flg && !redir_flg
			&& tok_len)
			break ;
		else if ((*seg == '<' || *seg == '>') && !quote_flg && !redir_flg)
			redir_flg = set_redir_type(token, seg);
		if (is_white && !quote_flg && !redir_flg)
			break ;
		tok_len++;
		seg++;
	}
	return (tok_len);
}

void	extract_token(t_msh *msh, t_token **token, char *seg)
{
	int	tok_len;
	int	arr_len;
	int	skip;

	arr_len = 0;
	while (*seg)
	{
		*token = msh_realloc(*token, arr_len, (arr_len + 1), TOK);
		if (!*token)
			parse_error(msh, msh -> aux, NULL, "tokenization");
		ft_memset(&(*token)[arr_len], 0, sizeof(t_token));
		tok_len = get_token_len(seg, &(*token)[arr_len], 0, 0);
		skip = redir_skip(seg);
		(*token)[arr_len].token = ft_substr(seg, skip, tok_len - skip);
		if (!(*token)[arr_len].token)
			parse_error(msh, msh -> aux, NULL, "tokenization");
		seg += tok_len;
		skip_whitespaces(&seg);
		arr_len++;
	}
	*token = msh_realloc(*token, arr_len, (arr_len + 1), TOK);
	if (!*token)
		parse_error(msh, msh -> aux, NULL, "tokenization");
	ft_memset(&(*token)[arr_len], 0, sizeof(t_token));
}

void	seg_tokenize(t_msh *msh, t_parse *aux)
{
	char	**seg;
	t_token	**token;

	seg = aux -> seg;
	token = aux -> token;
	while (*seg)
	{
		extract_token(msh, token, *seg);
		seg++;
		token++;
	}
}
//MALLOC FAIL PROTECTION: CHECKED. except for case: line 81