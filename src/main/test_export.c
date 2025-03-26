#include "../../includes/minishell.h"

void	free_arr(char ***arr)
{
	char	**tmp;

	tmp = *arr;
	if (!tmp)
		return ;
	while (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	free(*arr);
	*arr = NULL;
}

static void	format_print_x_var(char *x_var)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(x_var, '=');
	if (eq)
	{
		key = ft_substr(x_var, 0, eq - x_var);
		if (!key)
			printf("\033[1;31mformat print c_var key error\n\033[0m");
		if (ft_strcmp(key, "_"))
			printf("declare -x %s=\"%s\"\n", key, eq + 1);
		free(key);
	}
	else
		printf("declare -x %s\n", x_var);	
}

static void    display_x_var(char **envl, char *floor)
{
    char    **lex_min;
    char    **iter;
    int	len;
    
    iter = envl;
    len = 0;
    while (iter[len])
        len++;
    while(len--)
    {
        lex_min = envl;
        iter = envl;
        while(*lex_min && !(ft_strcmp(*lex_min, floor) > 0))
            lex_min++;
        while (*iter)
        {
            if(ft_strcmp(*lex_min, *iter) > 0 && ft_strcmp(*iter, floor) > 0 )
                lex_min = iter;
            iter++;
        }
        format_print_x_var(*lex_min);
        floor = *lex_min;
    }  
}

void    add_env_var(t_msh *msh, char **envl, char *entry)
{
    int env_len;
    char **env_new;

    env_len = 0;
    while (envl[env_len])
        env_len++;
    env_new = ft_calloc(env_len + 2, sizeof(char *));
    if (!env_new)
        exit(printf("\033[1;31add_env_var env_new big array error\n\033[0m")); //TODO: 
    ft_memcpy(env_new, envl, env_len * sizeof(char *));
    env_new[env_len]  = ft_strdup(entry);
    if (!env_new[env_len])
        exit(printf("\033[1;31add_env_var env_new entry error\n\033[0m")); //TODO:
    env_new[++env_len] = NULL;
    free(envl);
    msh -> envl = env_new;
	printf("\033[1;32madd_env_var successful %s\n\033[0m", entry);
}

void    overwrite_env_var(char **env_var, char *entry)
{
    free(*env_var);
    *env_var = ft_strdup(entry);// this will only replace the existing 
    if (!*env_var)
        exit(printf("\033[1;31moverwrite env_var error %s\n\033[0m", entry));//TODO: clean "key". the cmd will be leaned later in relevant cleaning fuunction.
printf("\033[1;32moverwrite successful %s\n\033[0m", entry);
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
		printf("\033[1;31mset env key error\n\033[0m");//TODO: error
    k_len = ft_strlen(key);
    env_iter = envl;
    while (*env_iter && !(!ft_strncmp(*env_iter, key, k_len) 
            && (*(*env_iter + k_len) == '\0' || *(*env_iter + k_len) == '=')))
		env_iter++;
    free(key);
    if (!*env_iter)
        return(add_env_var(msh, envl, entry));// what if something happen in this function and it exits from there. is t okay to use it in a return?
    if (*(entry + k_len) == '=')
        return(overwrite_env_var(env_iter, entry));
}

static int is_valid_id(char *x_var)
{
    if (!*x_var || !(ft_isalpha(*x_var) || *x_var == '_'))
        return (0);
    while(*x_var && *x_var != '=')
    {
        if (!ft_isalnum(*x_var) && *x_var != '_')
            return (0);
        x_var++;
    }
    return (1);
}

void    builtin_export(t_msh *msh, char **cmd)
{
    if (!*(++cmd))
        return (display_x_var(msh -> envl, ""));
    while (*cmd)
    {
        if(!is_valid_id(*cmd))
            printf("\033[1;31mminishell: export: `%s': not a valid identifier\n\033[0m", *cmd);//TODO:Errpr
        else
            set_env(msh, msh -> envl, *cmd);
        cmd++;
    }
}

void	duplicate_env(t_msh *msh, char **envp)
{
	int	env_len;
	char **tmp_p;

	env_len = 0;
	// if (!envp || !*envp)
	// 	return(generate_mini_env(msh));
	while (envp[env_len])
		env_len++;
	msh -> envl = ft_calloc(env_len + 1 ,sizeof(char *));
	if (!msh -> envl)
		exit(printf("\033[1;31mduplicate env msh _> envl error\n\033[0m"));//TODO
	tmp_p = msh -> envl;
	while (*envp)
	{
		*tmp_p = ft_strdup(*envp);
		if (!*tmp_p)
			exit(printf("\033[1;31mduplicate env tmp_p error\n\033[0m"));//TODO
		tmp_p++;
		envp++;
	}
	*tmp_p = NULL;
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

void print_envl(t_msh	*msh) //SUCCESS: unit test for envl duplication.
{
	char **tmp;

	tmp = msh -> envl;
	while (*tmp)
	{
		printf("%s\n", *tmp);
		tmp++;
	}
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
	printf("\033[1;34m\n\nprinting X_VAR before export\n\033[0m");
    display_x_var(msh.envl, "");
	builtin_export(&msh, cmd);
	printf("\033[1;34m\n\nprinting X_VAR\n\033[0m");
    display_x_var(msh.envl, "");
	printf("\033[1;34m\n\nprinting envl after export\n\033[0m");
	print_envl(&msh);
	msh_clean(&msh);
    return (0);
}
