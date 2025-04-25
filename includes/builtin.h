/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:51:51 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/25 22:32:43 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//cd
void    builtin_cd(t_msh *msh, char **cmd);
void    cd_path(t_msh *msh, char *path);
void    cd_tilde(t_msh *msh, char *tilde_path);
void    cd_env_var(t_msh *msh, char *dir);
void    msh_wd_update(t_msh *msh);
void    handle_unlinked_cwd(t_msh *msh, char *path);

//echo
void    builtin_echo(t_msh *msh, char **cmd);

//env
void    builtin_env(t_msh *msh, char **cmd);

//exit
void    builtin_exit(t_msh *msh, char **cmd);
int is_numeric(char *str);

//export
void    builtin_export(t_msh *msh, char **cmd);
int is_valid_id(char *x_var);

//pwd
void    builtin_pwd(t_msh *msh);

//unset
void    builtin_unset(t_msh *msh, char **cmd);
void    unset_env(t_msh *msh, char **envl, char *key);

//exec_builtin
void execin_shell(t_msh *msh, char **cmd);
void exec_builtin(t_msh *msh, char **cmd);
int is_builtin(char **cmd);
#endif