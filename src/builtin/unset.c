/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:57:30 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/29 04:05:24 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    unset_env(t_msh *msh, char **envl, char *key)
{
    int env_len;
    int k_len;
    char **env_iter;

    env_len = 0;
    while (envl[env_len])
        env_len++;
    k_len = ft_strlen(key);
    env_iter = envl;
    while (*env_iter && !(!ft_strncmp(*env_iter, key, k_len) 
            && (*(*env_iter + k_len) == '\0' || *(*env_iter + k_len) == '=')))
		env_iter++;
    if (!*env_iter)
        return;
    free(*env_iter);
    ft_memmove(env_iter + 1, env_iter, (env_len - (env_iter + 1 - envl)));
    envl[env_len - 1]  = NULL;
} // an allocated memory block id left unused after this, it's not nice 
//that we allocate again if we have to set a variable after this, think about it. 
//my initial solution was to make envl a vector

void    builtin_unset(t_msh *msh, char **cmd)
{
    if (!*(++cmd))
        return ;
    while (*cmd)
    {
        if (!is_valid_id(*cmd) || ft_strchr(*cmd, '='))
            return ;
        else
            unset_env(msh, msh -> envl, *cmd);
        cmd++;
    }
}



