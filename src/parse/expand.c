/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 05:43:25 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_env_key(char **token)
{
	char	*start;
	int		var_len;

	var_len = 0;
	(*token)++;
	start = *token;
	while (**token && (ft_isalnum(**token) || **token == '_' || **token == '?'
			|| **token == '$'))
	{
		if (var_len == 0 || (**token != '?' && **token != '$'))
		{
			var_len++;
			(*token)++;
		}
		if ((start == *token - 1 && ft_isdigit(*(*token - 1)))
			|| (start == *token - 1 && *(*token - 1) == '?')
			|| (start == *token - 1 && *(*token - 1) == '$')
			|| **token == '?' || **token == '$')
			break ;
	}
	return (ft_substr(start, 0, var_len));
}

void	expand_parameter(t_msh *msh, t_token *token, t_expan *exp)
{
	char	*exp_val;
	char	*exp_dup;
	int		q_context;

	exp_dup = NULL;
	q_context = check_quotes(exp -> prefix, exp -> exp);
	exp_val = extract_exp_value(msh, exp -> key);
	if (exp_val)
		exp_dup = ft_strdup(exp_val);
	if (exp_val && !exp_dup)
		free(exp_val);
	if (!exp_dup)
		parse_error(msh, msh -> aux, exp, "parameter expansion");
	if (!get_tmp_arr(exp, exp_dup, q_context))
	{
		free(exp_val);
		parse_error(msh, msh -> aux, exp, "expansion array creation");
	}
	adjust_exp_edge(msh, exp, exp_val, q_context);
	revise_exp_arr(msh, token, exp);
}

void	expscan_token(t_msh *msh, t_token *token)
{
	t_expan	exp;

	init_exp(msh, *token, &exp);
	while (*(exp.suffix))
	{
		if (*(exp.suffix) == '$' && check_quotes(exp.tok, exp.suffix) != '\'')
		{
			exp.key = extract_env_key(&(exp.suffix));
			if (!exp.key)
				parse_error(msh, msh -> aux, &exp, "expansion token scan");
			if (*exp.key)
				expand_parameter(msh, token, &exp);
			else
				exp.key = free_and_null(exp.key);
		}
		if (*(exp.suffix) && !(*(exp.suffix) == '$' && check_quotes(exp.tok, exp.suffix) != '\''
				&& (ft_isalnum(*(exp.suffix + 1)) || *(exp.suffix + 1) == '_'
					|| *(exp.suffix + 1) == '?' || *(exp.suffix + 1) == '$')))
		{
			ft_memcpy(exp.exp, exp.suffix, sizeof(char));
			exp.suffix++;
			exp.exp++;
		}
	}
	clean_exp(&exp);
}

void	expand_tokens(t_msh *msh, t_token **token)
{
	char	*token_iter;
	t_token	*tok_tmp;

	while (*token)
	{
		tok_tmp = *token;
		while ((*tok_tmp).token)
		{
			token_iter = ft_strchr((*tok_tmp).token, '$');
			while (token_iter && *token_iter
				&& check_quotes((*tok_tmp).token, token_iter) == '\'')
				token_iter = ft_strchr((++token_iter), '$');
			if ((*tok_tmp).redir != REDIR_HDOC && token_iter
				&& check_quotes((*tok_tmp).token, token_iter) != '\'')
				expscan_token(msh, tok_tmp);
			(tok_tmp)++;
		}
		token++;
	}
}
//MALLOC FAIL PROTECTION: CHECKED.