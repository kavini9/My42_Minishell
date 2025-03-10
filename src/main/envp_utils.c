/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:53:48 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/11 00:00:45 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_env	*new_env_var(char *var, char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node != NULL)
	{
		node -> var = var;
		node -> val = val;
        node -> next = NULL;
	}
	return (node);
}

void get_envl(t_msh *msh, char **envp)
{
    char    eq;
    char    *var;
    char    *val;
    
	if (!envp || !*envp)
		return(set_basic_envl(msh, envp));
	while (*envp)
	{
        eq = ft_strchr(*envp, '=');
        var = 
        if (!msh -> envl)
            new_env_var()
        
		
	}
}