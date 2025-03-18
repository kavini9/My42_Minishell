/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:25:30 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/18 17:53:58 by wweerasi         ###   ########.fr       */
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