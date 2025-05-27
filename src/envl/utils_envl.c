/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:25:30 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/27 23:41:55 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char    *get_env(char **envl, char *var)
{
    size_t  var_len;
    
    if(!envl || !*var)
        return (NULL);
    var_len = ft_strlen(var);
    while (*envl)
    {
        if (ft_strncmp(*envl, var, var_len) && *(*envl + var_len) == '=')
            return (*envl + var_len + 1);//TODO; there's a case when we have to print the whole line not just the value.
        envl++;
    }
    return (NULL);
}

void    add_env_var(t_msh *msh, char **envl, char *entry)
{
    int env_len;
    char **env_new;
	char *tmp;

    env_len = 0;
    while (envl[env_len])
        env_len++;
    env_new = ft_calloc(env_len + 2, sizeof(char *));
    if (!env_new)
        msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "setenv");//"minishell: fatal error: memory allocation failed in %s\n" 
    ft_memcpy(env_new, envl, env_len * sizeof(char *));
	tmp = env_new[env_len - 1];
    env_new[env_len - 1]  = ft_strdup(entry);
    if (!env_new[env_len - 1])
    {
        free(env_new);
        msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "setenv");//"minishell: fatal error: memory allocation failed in %s\n"
    }
    env_new[env_len] = tmp;
    env_new[++env_len] = NULL;
    free(envl);
    msh -> envl = env_new;
	msh -> exit_code = EXIT_SUCCESS;
}

void    overwrite_env_var(t_msh *msh, char **env_var, char *entry)
{
    free(*env_var);
    *env_var = ft_strdup(entry);// this will only replace the existing 
    if (!*env_var)
        msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "setenv");//"minishell: fatal error: memory allocation failed in %s\n"
    msh -> exit_code = EXIT_SUCCESS;
}

void    set_env(t_msh *msh, char **envl, char *entry)
{  
    char    **env_iter;
    char    *eq;
    char    *key;
    int     k_len;

    eq = ft_strchr(entry, '=');
	if (eq)
		key = ft_substr(entry, 0, eq - entry);
    if (!eq)
		key = ft_strdup(entry);
	if (!key)
		msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "setenv");//"minishell: fatal error: memory allocation failed in %s\n"
    k_len = ft_strlen(key);
    env_iter = envl;
    while (*env_iter && !(!ft_strncmp(*env_iter, key, k_len) 
            && (*(*env_iter + k_len) == '\0' || *(*env_iter + k_len) == '=')))
		env_iter++;
    free(key);
    if (!*env_iter)
        return(add_env_var(msh, envl, entry));// what if something happen in this function and it exits from there. is t okay to use it in a return?
    if (*(entry + k_len) == '=')
        return(overwrite_env_var(msh, env_iter, entry));
}
  
void    update_env(t_msh *msh, char *key, char *value)
{
    char *entry;

    entry = ft_strjoin(key, value);
    if(!entry)
        msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "update_env");//who cleans key coming from shlvl
    set_env(msh, msh -> envl, entry);
}    
    