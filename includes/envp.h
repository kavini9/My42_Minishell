/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:50:35 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/25 22:35:00 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "minishell.h"

void	duplicate_env(t_msh *msh, char **envp);
void	generate_mini_env(t_msh *msh);
void	set_shlvl(t_msh *msh, char **envl);

char    *get_env(char **envl, char *var);
void    update_env(t_msh *msh, char *key, char *value);
void    set_env(t_msh *msh, char **envl, char *entry);
void    add_env_var(t_msh *msh, char **envl, char *entry);
void    overwrite_env_var(t_msh *msh, char **env_var, char *entry);
#endif