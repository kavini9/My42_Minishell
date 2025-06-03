#include "includes/minishell.h"

#define FULL_LINE -1

void msh_init(t_msh *msh, char **envp)
{
	ft_memset(msh, 0, sizeof(t_msh)); //DES: sets everything to NULL
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		msh_error(msh, (ERRNO|LOG|CLEAN|EXIT) << 8 | 1, ERR_GETCWD, "init");//"minishell: cd: error retrieving current directory: getcwd: %s\n"
	msh -> old_wd = ft_strdup(msh -> cwd);//if we go one level up the old pwd is different
	if (!msh -> old_wd)
		msh_error(msh, LOG|CLEAN|EXIT << 8 | 1 , ERR_MALLOC, NULL);//"minishell: fatal error: memory allocation failed in %s.\n"
	//duplicate_env(msh, envp);
	//set_shlvl(msh, msh -> envl);
}

#include "../includes/minishell.h"

int main(void)
{
    t_msh msh;
    char *line;

    msh_init(&msh, NULL);
    while (1)
    {
        line = readline("validator> ");
        if (!line || !*line)
            continue;
        if (!ft_strcmp(line, "exit"))
            break;
        if (msh_validate_line(&msh, &line))
            printf("-> ❌ Invalid input (exit_code = %d)\n\n", msh.exit_code);
        else
            printf("-> ✅ Valid input\n\n");
        free(line);
    }
    return 0;
}
