/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:08:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 07:30:04 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_msh *msh)// char **cmd)
{
	char	**envl;

	envl = msh -> envl;
	while (*envl)
	{
		if (ft_strchr(*envl, '='))
			printf("%s\n", *envl);
		envl++;
	}
	msh -> exit_code = EXIT_SUCCESS;
}
