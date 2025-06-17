/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_array_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 04:59:45 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_arrlen(void **arr)
{
	size_t	len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

void	concat_exp_edge(t_msh *msh, t_expan *exp, int spc, int index)
{
	char	*tmp;

	if (spc == 0)
		tmp = ft_strjoin(exp -> prefix, exp -> tmp_arr[index]);
	else
	{
		exp -> scan_offset = ft_strlen(exp -> tmp_arr[index]);
		tmp = ft_strjoin(exp -> tmp_arr[index], exp -> suffix);
	}
	if (!tmp)
		parse_error(msh, msh -> aux, exp, "expansion array concatenation");
	free((exp -> tmp_arr[index]));
	exp -> tmp_arr[index] = tmp;
}

void	extend_exp_edge(t_msh *msh, t_expan *exp, int index, int *len)
{
	if ((index == 0 && !*exp -> prefix) || (index > 0 && !*exp -> suffix))
		return ;
	exp -> tmp_arr = msh_realloc(exp -> tmp_arr, (*len + 1), (*len + 2), ARR);
	if (!exp -> tmp_arr)
		parse_error(msh, msh -> aux, exp, "expansion array extension");
	if (index == 0)
	{
		ft_memmove(exp -> tmp_arr + 1, exp -> tmp_arr, (*len) * sizeof(char *));
		*(exp -> tmp_arr) = strdup(exp -> prefix);
	}
	else
	{
		exp -> tmp_arr[index] = ft_strdup(exp -> suffix);
		exp -> tmp_arr[index + 1] = NULL;
	}
	if (!exp -> tmp_arr[index])
		parse_error(msh, msh -> aux, exp, "expansion array extension");
	(*len)++;
}

void	adjust_exp_edge(t_msh *msh, t_expan *exp, char *exp_val, int q_context)
{
	int	lead_spc;
	int	trail_spc;
	int	len;

	len = 0;
	lead_spc = 0;
	trail_spc = 0;
	if (exp_val)
		len = ft_strlen(exp_val);
	if (len > 0 && !q_context)
	{
		lead_spc = (ft_strchr(" \t\n\r\f\v", exp_val[0]) != NULL);
		trail_spc = (ft_strchr(" \t\n\r\f\v", exp_val[len - 1]) != NULL);
	}
	free(exp_val);
	len = ft_arrlen((void **) exp -> tmp_arr);
	if (!lead_spc)
		concat_exp_edge(msh, exp, 0, 0);
	else
		extend_exp_edge(msh, exp, 0, &len);
	if (!trail_spc)
		concat_exp_edge(msh, exp, len, len - 1);
	else
		extend_exp_edge(msh, exp, len, &len);
}

char	**get_tmp_arr(t_expan *exp, char *exp_dup, int q_context)
{
	char	*tmp_exp_dup;

	tmp_exp_dup = exp_dup;
	skip_whitespaces(&tmp_exp_dup);
	if (*exp_dup && *tmp_exp_dup && !q_context)
	{
		tmp_exp_dup = exp_dup;
		while (*tmp_exp_dup)
		{
			if (ft_strchr("\t\n\r\f\v", *tmp_exp_dup))
				*tmp_exp_dup = ' ';
			tmp_exp_dup++;
		}
		exp -> tmp_arr = ft_split(exp_dup, ' ');
		free(exp_dup);
	}
	else
	{
		exp -> tmp_arr = ft_calloc(2, sizeof(char *));
		if (exp -> tmp_arr)
			*(exp -> tmp_arr) = exp_dup;
		else
			free(exp_dup);
	}
	return (exp -> tmp_arr);
}

//MALLOC FAIL PROTECTION: CHECKED. except for case: line 37, 49, 59 