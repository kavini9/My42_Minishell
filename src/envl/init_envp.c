/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:53:48 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/15 03:57:19 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	set_shlvl(t_msh *msh, char **envl)
{
	char *cur_lvl;
	char *nxt_lvl;
	int	lvl_val;

	cur_lvl = get_env(envl, "SHLVL");
	if (cur_lvl)
		lvl_val = ft_atoi(cur_lvl);
	else
		lvl_val = 0;
	lvl_val++;
	nxt_lvl = ft_itoa(lvl_val);
	if (!nxt_lvl)
		msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "set_shlvl");
	update_env(msh, "SHLVL=", nxt_lvl);
}

void	generate_mini_env(t_msh *msh)
{
	char **tmp_p;
	
	msh -> envl = ft_calloc(5 ,sizeof(char *));
	if (!msh -> envl)
		msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "minimal envp");
	tmp_p = msh -> envl;
	*tmp_p = ft_strjoin("PWD=", msh -> cwd);
	if (!*tmp_p)
		msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "PWD");
	*(++tmp_p) = ft_strdup("SHLVL=1");
	if (!*tmp_p)
		msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "SHLVL");
	*(++tmp_p) = ft_strdup("_=]");
	if (!*tmp_p)
		msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "_");
	*(++tmp_p) = NULL;
	*(++tmp_p) = NULL;
}

void	duplicate_env(t_msh *msh, char **envp)
{
	int	env_len;
	char **tmp_p;

	env_len = 0;
	if (!envp || !*envp)
		return(generate_mini_env(msh));
	while (envp[env_len])
		env_len++;
	msh -> envl = ft_calloc(env_len + 1 ,sizeof(char *));
	if (!msh -> envl)
		msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "envp");
	tmp_p = msh -> envl;
	while (*envp)
	{
		*tmp_p = ft_strdup(*envp);
		if (!*tmp_p)
			msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "env var");//how to clean this? no worries temp p is NULL.
		tmp_p++;
		envp++;
	}
	*tmp_p = NULL;
}
