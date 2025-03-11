/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:53:48 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/11 22:55:04 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

// t_env	*new_env_var(char *var, char *val, int var_len)
// {
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	if (node != NULL)
// 	{
// 		ft_memcpy(node -> var, (const void *) var, var_len);
// 		node -> val = val;
//         node -> next = NULL;
// 	}
// 	return (node);
// }

// void duplicate_env(t_msh *msh, char **envp)
// {
//     char    eq;
//     char    *val;
    
// 	if (!envp || !*envp)
// 		return(gen_basic_envl(msh, envp));
// 	while (*envp)
// 	{
//         eq = ft_strchr(*envp, '=');
//         if (!msh -> envl)
//             new_env_var(*envp, eq + 1, (eq - *envp));
// 	}
// }

void	generate_mini_env(t_msh *msh, char **envp)
{
	msh -> envl = ft_calloc(5 ,sizeof(char *));
	*msh -> envl = ft_strjoin("PWD=", msh -> cwd);
	if (!*msh -> envl)
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating pwd for basic env.
	*(++msh -> envl) = ft_strdup("SHLVL=1");
	if (!*msh -> envl)
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating pwd for basic env.
	*(++msh -> envl) = ft_strdup("_=]");
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating pwd for basic env.
	*(++msh -> envl) = NULL;
	*(++msh -> envl) = NULL;
}

void	duplicate_env(t_msh *msh, char **envp)
{
	int	env_len;

	env_len = 0;
	if (!envp || !*envp)
		return(generate_mini_env(msh, envp));
	while (envp[env_len])
		env_len++;
	msh -> envl = ft_calloc(env_len + 1 ,sizeof(char *));
	if (!msh -> envl)
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating env list.
	while (*envp)
	{
		*msh -> envl = ft_strdup(*envp);
		if (!*msh -> envl)
			exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when duplicating environment variables
		msh -> envl++;
		envp++;
	}
	*msh -> envl = NULL;
}
