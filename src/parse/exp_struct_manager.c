/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_struct_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:32:19 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 04:47:33 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_exp_state(t_msh *msh, t_token *token, t_expan *exp)
{
	int	index;

	free(exp -> prefix);
	free(exp -> tok);
	if (token -> expn_len - 1 > 0)
		index = token -> expn_len - 1;
	else
		index = 0;
	exp -> tok = ft_strdup(token -> expn[index]);
	if (!exp -> tok)
		parse_error(msh, msh -> aux, exp, "expansion util struct update");
	exp -> suffix = exp -> tok + exp -> scan_offset;
	exp -> prefix = ft_calloc(ft_strlen(exp -> tok), sizeof(char));
	if (!exp -> prefix)
		parse_error(msh, msh -> aux, exp, "expansion util struct update");
	ft_memcpy(exp -> prefix, exp -> tok, exp -> scan_offset * sizeof(char));
	exp -> exp = exp -> prefix + exp -> scan_offset;
	free(exp -> key);
	exp -> key = NULL;
	free(exp -> tmp_arr);
	exp -> tmp_arr = NULL;
	exp -> scan_offset = 0;
}

void	revise_exp_arr(t_msh *msh, t_token *token, t_expan *exp)
{
	int	exp_len;
	int	tmp_len;
	int	size;
	int	new_exp_len;

	exp_len = token -> expn_len;
	size = sizeof(char *);
	tmp_len = ft_arrlen((void **) exp -> tmp_arr);
	if (!exp_len)
		new_exp_len = tmp_len + 1;
	else
		new_exp_len = exp_len + tmp_len;
	token -> expn = msh_realloc(token -> expn, exp_len, new_exp_len, ARR);
	if (!token -> expn)
		parse_error(msh, msh -> aux, exp, "expansion util struct revise");
	if (exp_len > 0)
	{
		free(*((token -> expn) + exp_len - 1));
		ft_memcpy((token -> expn) + exp_len - 1, exp -> tmp_arr,
			tmp_len * sizeof(char *));
	}
	else
		ft_memcpy((token -> expn), exp -> tmp_arr, tmp_len * sizeof(char *));
	token -> expn_len = new_exp_len - 1;
	update_exp_state(msh, token, exp);
}

void	init_exp(t_msh *msh, t_token token, t_expan *exp)
{
	ft_memset(exp, 0, sizeof(t_expan));
	exp -> tok = ft_strdup(token.token);
	if (!exp -> tok)
		parse_error(msh, msh -> aux, exp, "expansion util struct init");
	exp -> suffix = token.token;
	exp -> prefix = ft_calloc(ft_strlen(token.token), sizeof(char));
	if (!exp -> prefix)
		parse_error(msh, msh -> aux, exp, "expansion util struct init");
	exp -> exp = exp -> prefix;
}
