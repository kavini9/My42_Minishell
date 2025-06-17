/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:22:43 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 08:26:40 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_msh *msh)
{
	if (msh -> cwd)
	{
		printf("%s\n", msh -> cwd);
		msh -> exit_code = EXIT_SUCCESS;
	}
	else
	{
		msh -> cwd = getcwd(NULL, 0);
		if (!msh -> cwd)
			return (msh_error(msh, (ERRNO | LOG | CLEAN) << 8 | 1, ERR_GETCWD,
					"cd"));
		builtin_pwd(msh);
	}
}
