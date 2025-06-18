/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_unlinked_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:12:52 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 15:08:48 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_unlinked_cwd(t_msh *msh, char *path)
{
	char	*tmp;
	char	*new_wd;

	msh_error(msh, LOG << 8 | 1, "minishell: cd: error retrieving current "
		"directory: getcwd: cannot access parent directories: %s\n",
		strerror(ENOENT));
	new_wd = ft_strjoin("/", path);
	tmp = new_wd;
	if (tmp)
		new_wd = ft_strjoin(msh -> cwd, tmp);
	free(tmp);
	if (!new_wd)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "cd");
	free(msh -> old_wd);
	msh -> old_wd = ft_strdup(msh -> cwd);
	if (!msh -> old_wd)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "cd");
	free(msh -> cwd);
	msh -> cwd = new_wd;
	update_env(msh, "OLDPWD=", ft_strdup(msh -> old_wd));
	update_env(msh, "PWD=", ft_strdup(msh -> cwd));
	msh -> exit_code = EXIT_SUCCESS;
}
