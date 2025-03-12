/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:53:48 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/12 15:44:03 by wweerasi         ###   ########.fr       */
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

void	generate_mini_env(t_msh *msh)
{
	char **tmp_p;
	
	msh -> envl = ft_calloc(5 ,sizeof(char *));
	if (!msh -> envl)
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating pwd for basic env.
	tmp_p = msh -> envl;
	*tmp_p = ft_strjoin("PWD=", msh -> cwd);
	if (!*tmp_p)
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating pwd for basic env.
	*(++tmp_p) = ft_strdup("SHLVL=1");
	if (!*tmp_p)
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating pwd for basic env.
	*(++tmp_p) = ft_strdup("_=]");
	if (!*tmp_p)
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating pwd for basic env.
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
		exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when creating env list.
	tmp_p = msh -> envl;
	while (*envp)
	{
		*tmp_p = ft_strdup(*envp);
		if (!*tmp_p)
			exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail when duplicating environment variables
		tmp_p++;
		envp++;
	}
	*tmp_p = NULL;
}
