/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:57:30 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 08:25:47 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_env(char **envl, char *key)
{
	int		env_len;
	int		k_len;
	char	**env_iter;

	env_len = 0;
	while (envl[env_len])
		env_len++;
	k_len = ft_strlen(key);
	env_iter = envl;
	while (*env_iter && !(!ft_strncmp(*env_iter, key, k_len)
			&& (*(*env_iter + k_len) == '\0' || *(*env_iter + k_len) == '=')))
		env_iter++;
	if (!*env_iter)
		return ;
	free(*env_iter);
	ft_memmove(env_iter, env_iter + 1,
		(env_len - (env_iter + 1 - envl)) * sizeof(char *));
	envl[env_len - 1] = NULL;
}

void	builtin_unset(t_msh *msh, char **cmd)
{
	if (!*(++cmd))
		return ;
	while (*cmd)
	{
		if (!is_valid_id(*cmd) || ft_strchr(*cmd, '='))
			return ;
		else
			unset_env(msh -> envl, *cmd);
		cmd++;
	}
	msh -> exit_code = EXIT_SUCCESS;
}
