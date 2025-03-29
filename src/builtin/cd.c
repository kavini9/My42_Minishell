/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:09:42 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/29 00:55:00 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void    handle_unlinked_cwd(t_msh *msh, char *path)
{
    char *tmp;
    char *new_wd;
    
    printf(STDERR_FILENO, "minishell: cd: error retrieving current "
		"directory: getcwd: cannot access parent directories: ");
    perror("");
    new_wd = ft_strjoin("/", path);
    tmp = new_wd;
    if (tmp)
         new_wd = ft_strjoin(msh -> cwd, tmp);
    free(tmp);
    if (!new_wd)  
        exit(printf("Error\n"));
    free(msh -> old_wd);
    msh -> old_wd = ft_strdup(msh -> cwd);
    if (!msh -> old_wd)
        exit(printf("\033[1;31mmsh -> old_wd error\n\033[0m"));//TODO: malloc error.
    free(msh -> cwd);
    msh -> cwd = new_wd; //I am not strdupping this. just assigning this thinking it won't cause a problem.
    update_env(msh, "OLDPWD=", msh -> old_wd);
    update_env(msh, "PWD=", msh -> cwd);
}

void    msh_wd_update(t_msh *msh)
{
    free(msh -> old_wd);
    msh -> old_wd = ft_strdup(msh -> cwd);
	if (!msh -> old_wd)
		exit(printf("\033[1;31mmsh -> old_wd error\n\033[0m"));
    free(msh -> cwd);
    msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		exit(printf("\033[1;31mmsh -> wd error\n\033[0m"));
    update_env(msh, "OLDPWD=", msh -> old_wd);
    update_env(msh, "PWD=", msh -> cwd);
}

void    cd_env_var(t_msh *msh, char *dir)
{
    char    *path;
    
    path = get_env(msh -> envl, dir);
    if (!path)
        return (msh_warning("minishell: cd:", dir , "not set", NULL));//take care of the return value in each error.
    if (chdir(path) == -1)
        msh_error(msh, printf("minishell: cd"));//msh_error(msh, perror("minishell: cd"));//TODO: this should exit minishell.
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
    msh_error(msh, LOG|CLEAN|EXIT, ERR_MALLOC, NULL);//ERROR_MESSAGE
    if (chdir(path) == -1)
    {
        free(path);
        msh_error(msh, LOG, ERR_SYS_FUNC, "getcwd");//ERROR_MESSAGE
        msh_error(msh, printf("minishell: cd"));//msh_error(msh, perror("minishell: cd"));//TODO: this should exit minishell.
    }
    free(path);
    return(pwd_update(msh));//TODO: write functon. 
}

//cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
void    cd_path(t_msh *msh, char *path)
{
    char    *cwd;
    
    if (chdir(path) == -1)
        return(msh_error(msh, LOG, ERR_SYS_FUNC, "chdir"));//ERROR_MESSAGE
    cwd = getcwd(NULL, 0);
    if (!cwd && errno == ENOENT)
        return(handle_unlinked_cwd(msh, path));  //TODO:write function
    else if (!cwd)
        msh_error(msh, LOG, ERR_SYS_FUNC, "getcwd");//ERROR_MESSAGE
    free(cwd);
    return (pwd_update(msh));
}

void    builtin_cd(t_msh *msh, char **cmd)
{
    if (cmd[2])
        msh_error("minishell: cd: too many arguments\n");//TODO: should not exit minishell but prints error message.
    else if (!cmd[1] || ft_strcmp(cmd[1], "~") || ft_strcmp(cmd[1], "--"))//DES: -- used with -filename to indicate end of options.
        cd_env_var(msh, "HOME");
    else if (cmd[1][0] == '~')
        cd_tilde(msh, cmd[1]);
    else if (ft_strcmp(cmd[1], "-"))
        cd_env_var(msh, "OLDPWD");
    else
        cd_path(msh, cmd[1]);
}

//TODO: find a way to update exit status