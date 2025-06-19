/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:25:30 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/19 15:49:16 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(char **envl, char *var)
{
	size_t	var_len;

	if (!envl || !*var)
		return (NULL);
	var_len = ft_strlen(var);
	while (*envl)
	{
		if (!ft_strncmp(*envl, var, var_len) && *(*envl + var_len) == '=')
			return (*envl + var_len + 1);
		envl++;
	}
	return (NULL);
}

void	add_env_var(t_msh *msh, char **envl, char *entry)
{
	int		env_len;
	char	**env_new;
	char	*tmp;

	env_len = 0;
	while (envl[env_len])
		env_len++;
	env_new = ft_calloc(env_len + 2, sizeof(char *));
	if (!env_new)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "setenv");
	ft_memcpy(env_new, envl, env_len * sizeof(char *));
	tmp = env_new[env_len - 1];
	env_new[env_len - 1] = ft_strdup(entry);
	if (!env_new[env_len - 1])
	{
		free(env_new);
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "setenv");
	}
	free(entry);
	env_new[env_len] = tmp;
	env_new[++env_len] = NULL;
	free(envl);
	msh -> envl = env_new;
	msh -> exit_code = EXIT_SUCCESS;
}

void	overwrite_env_var(t_msh *msh, char **env_var, char *entry)
{
	free(*env_var);
	*env_var = ft_strdup(entry);
	if (!*env_var)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "setenv");
	free(entry);
	msh -> exit_code = EXIT_SUCCESS;
}

void	set_env(t_msh *msh, char **envl, char *entry)
{
	char	**env_iter;
	char	*eq;
	char	*key;
	int		k_len;

	if (!entry)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "setenv");
	eq = ft_strchr(entry, '=');
	if (eq)
		key = ft_substr(entry, 0, eq - entry);
	if (!eq)
		key = ft_strdup(entry);
	if (!key && bullshit_line_saving_free(entry))
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC, "setenv");
	k_len = ft_strlen(key);
	env_iter = envl;
	while (*env_iter && !(!ft_strncmp(*env_iter, key, k_len)
			&& (*(*env_iter + k_len) == '\0' || *(*env_iter + k_len) == '=')))
		env_iter++;
	free(key);
	if (!*env_iter)
		return (add_env_var(msh, envl, entry));
	if (*(entry + k_len) == '=')
		return (overwrite_env_var(msh, env_iter, entry));
	free(entry);
}

void	update_env(t_msh *msh, char *key, char *value)
{
	char	*entry;

	entry = NULL;
	if (!value)
		msh_error(msh, (LOG | CLEAN | EXIT) << 8 | 1, ERR_MALLOC,
			"update env");
	if (key && value)
		entry = ft_strjoin(key, value);
	if (value)
		free(value);
	set_env(msh, msh -> envl, entry);
}
