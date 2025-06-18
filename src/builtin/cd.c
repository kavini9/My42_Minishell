/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:09:42 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 20:02:38 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	msh_wd_update(t_msh *msh)
{
	free(msh -> old_wd);
	msh -> old_wd = ft_strdup(msh -> cwd);
	if (!msh -> old_wd)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "cd");
	free(msh -> cwd);
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		return (msh_error(msh, (ERRNO | LOG | CLEAN) << 8 | 1, CWD,
				"cd"));
	update_env(msh, "OLDPWD=", ft_strdup(msh -> old_wd));
	update_env(msh, "PWD=", ft_strdup(msh -> cwd));
	msh -> exit_code = EXIT_SUCCESS;
}

void	cd_env_var(t_msh *msh, char *dir)
{
	char	*path;

	path = get_env(msh -> envl, dir);
	if (!path)
		return (msh_error(msh, (LOG) << 8 | 1, ERR_DIR_NOTSET, dir));
	if (chdir(path) == -1)
		return (msh_error(msh, (ERRNO | LOG) << 8 | 1, ERR_CHDIR, path));
	if (!ft_strcmp(dir, "OLDPWD"))
		printf("%s\n", path);
	return (msh_wd_update(msh));
}

void	cd_tilde(t_msh *msh, char *tilde_path)
{
	char	*home;
	char	*path;

	home = get_env(msh -> envl, "HOME");
	if (!home)
		return (msh_error(msh, (LOG) << 8 | 1, ERR_DIR_NOTSET, "HOME"));
	path = ft_strjoin(home, tilde_path + 1);
	if (!path)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "cd");
	if (chdir(path) == -1)
	{
		msh_error(msh, (ERRNO | LOG) << 8 | 1, ERR_CHDIR, path);
		return (free(path));
	}
	free(path);
	return (msh_wd_update(msh));
}

void	cd_path(t_msh *msh, char *path)
{
	char	*cwd;

	if (chdir(path) == -1)
		return (msh_error(msh, (ERRNO | LOG) << 8 | 1, ERR_CHDIR, path));
	cwd = getcwd(NULL, 0);
	if (!cwd && errno == ENOENT)
		return (handle_unlinked_cwd(msh, path));
	else if (!cwd)
		return (msh_error(msh, (ERRNO | LOG | CLEAN) << 8 | 1, CWD,
				"cd"));
	free(cwd);
	return (msh_wd_update(msh));
}

void	builtin_cd(t_msh *msh, char **cmd)
{
	if (cmd[1] && cmd[2])
		return (msh_error(msh, LOG << 8 | 1, ERR_XTRA_ARG, "cd"));
	else if (!cmd[1] || !ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1], "--"))
		cd_env_var(msh, "HOME");
	else if (cmd[1][0] == '~')
		cd_tilde(msh, cmd[1]);
	else if (!ft_strcmp(cmd[1], "-"))
		cd_env_var(msh, "OLDPWD");
	else
		cd_path(msh, cmd[1]);
}
