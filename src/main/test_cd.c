# include "../../includes/minishell.h"

void    handle_unlinked_cwd(t_msh *msh, char *path)
{
    ft_printf_fd(STDERR_FILENO, "minishell: cd: error retrieving current "
		"directory: getcwd: cannot access parent directories: ");//TODO: Error message rinting
    
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
}

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
    return(msh_wd_update(msh));//TODO: write update pwd.
}

void    cd_tilde(t_msh *msh, char *tilde_path)
{
    char    *home;
    char    *path;
    
    home = get_env(msh -> envl, "HOME");
    if (!home)
        return (msh_warning("minishell: cd: HOME not set"));//TODO:
    path = ft_strjoin(home, tilde_path + 1);
    if (!path)
    msh_error(msh, LOG|CLEAN|EXIT, ERR_MALLOC, NULL);//ERROR_MESSAGE
    if (chdir(path) == -1)
    {
        free(path);
        msh_error(msh, LOG, ERR_SYS_FUNC, "getcwd");//ERROR_MESSAGE
        msh_error(msh, perror("minishell: cd"));//TODO: this should exit minishell.
    }
    free(path);
    return(msh_wd_update(msh));//TODO: write functon. 
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
    return (msh_wd_update(msh));
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

void msh_init(t_msh *msh, char **envp)
{
	ft_memset(msh, 0, sizeof(t_msh)); //DES: sets everything to NULL
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		exit(printf("\033[1;31mmsh -> wd error\n\033[0m"));
	msh -> old_wd = ft_strdup(msh -> cwd);
	if (!msh -> old_wd)
		exit(printf("\033[1;31mmsh -> old_wd error\n\033[0m"));
	duplicate_env(msh, envp);
}

void msh_clean(t_msh *msh)
{
	if (msh -> cwd)
		free(msh -> cwd);
	if (msh -> old_wd)
		free(msh -> old_wd);
	if (msh -> envl)
		free_arr(&msh -> envl);
	//if (msh -> token);
	//   delete_list(msh -> token);
	ft_memset(msh, 0, offsetof(t_msh, exit_code));
}

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;
	char 	**cmd;
	(void) av;
	
	cmd = av + 1;
	if (ac < 2)
		exit(printf("error\n"));
	msh_init(&msh, envp);
	bultin_cd(&msh, cmd);
//	printf("\033[1;34m\n\nprinting X_VAR\n\033[0m");
//	printf("\033[1;34m\n\nprinting envl after export\n\033[0m");
	msh_clean(&msh);
    return (0);
}
