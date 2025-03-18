/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:09:42 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/18 19:09:35 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    cd_env_var(t_msh *msh, char *dir)
{
    char    *path;
    
    path = get_env(msh -> envl, dir);
    if (!path)
        return (msh_warning("minishell: cd:", dir , "not set", NULL));//take care of the return value in each error.
    if (chdir(path) == -1)
        msh_error(msh, perror("minishell: cd"));//TODO: this should exit minishell.
    if (ft_strcmp(dir, "OLDPWD"))
        printf("%s\n", path);
    return(pwd_update(msh));//TODO: write update pwd.
}

void    cd_tilde(t_msh *msh, char *tilde_path)
{
    char    *home;
    char    *path;
    
    home = get_env(msh -> envl, "HOME");
    if (!home)
        return (msh_warning("minishell: cd: HOME not set"));
    path = ft_strjoin(home, tilde_path + 1);
    if (!path)
        exit(msh_clean(msh , err_out(ERROR_MSG)));//TODO: malloc fail joining home and tilde path.
    if (chdir(path) == -1)
    {
        free(path);
        msh_error(msh, perror("minishell: cd"));//TODO: this should exit minishell.
    }
    free(path);
    return(pwd_update(msh));//TODO: write functon. 
}

void    cd_path(t_msh *msh, char *path)
{
    char    *cwd;
    
    if (chdir(path) == -1)
        return (msh_warning("minishell: cd:", path , perror(""), NULL));//TODO: create mechanism to write error messages.
    cwd = getcwd(NULL, 0);
    if (!cwd && errno == ENOENT)
        return(unlinked_cwd(msh, path));  //TODO:write function
    else if (!cwd)
        exit(msh_clean(msh, err_out(strerror(errno))));//TODO: sysfunc getcwd failed.
    free(cwd);
    return (pwd_update(msh));
}

void    builtin_cd(t_msh *msh, char **cmd)
{
    if (cmd[2])
        msh_error("minishell: cd: too many arguments\n");//TODO: should not exit minishell but prints error message.
    else if (!cmd[1] || ft_strcmp(cmd[1], "~") || ft_strcmp(cmd[1], "--"))//DES: used with -filename to indicate end of options.
        cd_env_var(msh, "HOME");
    else if (cmd[1][0] == '~')
        cd_tilde(msh, cmd[1]);
    else if (ft_strcmp(cmd[1], "-"))
        cd_env_var(msh, "OLDPWD");
    else
        cd_path(msh, cmd[1]);
}