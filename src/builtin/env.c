/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:08:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/29 05:28:35 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    builtin_env(t_msh *msh, char **cmd)
{
    char **envl;

    envl = msh -> envl;
    // if (*(++cmd)) //removed this becase pwd still printf current directory even when "pwd asd asd"
    //     return(printf("minishell: env: %s: too many arguments\n", *cmd));//TODO
    while (*envl)
    {
        if (ft_strchr(*envl, '='))
            print("%s\n", *envl);
        envl++;
    }
}