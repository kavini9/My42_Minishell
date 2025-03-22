#include "../../includes/minishell.h"

static void	format_print_x_var(char *x_var)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(x_var, '=');
	key = ft_substr(x_var, 0, eq - x_var);
	if (!key)
		printf("error\n");
	printf("declare -x %s=\"%s\"\n", key, eq + 1);
	free(key);	
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
		exit(printf("error\n"));
	tmp_p = msh -> envl;
	while (*envp)
	{
		*tmp_p = ft_strdup(*envp);
		if (!*tmp_p)
			exit(printf("error\n"));
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
		exit(printf("error\n"));
	msh -> old_wd = ft_strdup(msh -> cwd);
	if (!msh -> old_wd)
		exit(printf("error\n"));
	duplicate_env(msh, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;
	(void) av;
	
	if (ac != 1)
		exit(printf("error\n"));
	msh_init(&msh, envp);
    display_x_var(msh.envl, "");
	//print_envl(&msh);
    return (0);
}
