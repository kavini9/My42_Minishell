/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:26:27 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/19 15:09:54 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_id(char *x_var)
{
	if (!*x_var || !(ft_isalpha(*x_var) || *x_var == '_'))
		return (0);
	while (*x_var && *x_var != '=')
	{
		if (!ft_isalnum(*x_var) && *x_var != '_')
			return (0);
		x_var++;
	}
	return (1);
}

static void	format_print_x_var(t_msh *msh, char *x_var)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(x_var, '=');
	if (eq)
	{
		key = ft_substr(x_var, 0, eq - x_var);
		if (!key)
			msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC,
				"export");
		if (ft_strcmp(key, "_"))
			printf("declare -x %s=\"%s\"\n", key, eq + 1);
		free(key);
	}
	else
		printf("declare -x %s\n", x_var);
}

static void	display_sorted_x_var(t_msh *msh, char **envl, char *floor)
{
	char	**lex_min;
	char	**iter;
	int		len;

	iter = envl;
	len = 0;
	while (iter[len])
		len++;
	while (len--)
	{
		lex_min = envl;
		iter = envl;
		while (*lex_min && !(ft_strcmp(*lex_min, floor) > 0))
			lex_min++;
		while (*iter)
		{
			if (ft_strcmp(*lex_min, *iter) > 0 && ft_strcmp(*iter, floor) > 0)
				lex_min = iter;
			iter++;
		}
		format_print_x_var(msh, *lex_min);
		floor = *lex_min;
	}
	msh -> exit_code = EXIT_SUCCESS;
}

void	builtin_export(t_msh *msh, char **cmd)
{
	if (!*(++cmd))
		return (display_sorted_x_var(msh, msh -> envl, ""));
	while (*cmd)
	{
		if (!is_valid_id(*cmd))
			msh_error(msh, LOG << 8 | 1, ERR_XPORTID,*cmd);
		else
			set_env(msh, msh -> envl, ft_strdup(*cmd));
		cmd++;
	}
}
