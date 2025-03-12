/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:32:56 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/12 16:08:59 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*prompt_gen(t_msh *msh)
// {
// 	if(ft_strcmp(msh -> cwd, msh -> old_wd)
// 		msh -> prompt = prompt_update(msh -> cwd);
// 	return(msh -> prompt)
// }

void msh_init(t_msh *msh, char **envp)
{
	ft_memset(msh, 0, sizeof(t_msh)); //DES: sets everything to NULL
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		exit(msh_clean(msh, err_out(strerror(errno))));//TODO: sysfunc getcwd failed.
	msh -> old_wd = ft_strdup(msh -> cwd);
	if (!msh -> old_wd)
		exit(msh_clean(msh, err_out(ERROR_MSG)));//TODO: ft_strdup: malloc fail when setting old working directory.
	duplicate_env(msh, envp);
}

void	msh_loop(t_msh *msh)
{
	char	*line;
	
	(void) *msh;
	while(1)
	{
		line = readline("minishell> ");
		if (*line)
		{
			add_history(line);
			printf("line entered: %s\n", line);
//			msh_parse(msh, line);//DES: parse and tokenize and add the list of tokens to msh -> token.
			if (!ft_strcmp(line, "exit"))
				break; 
		}
	}
	rl_clear_history();
}

int err_out(char *msg)
{
	printf("minishell: error: exiting with exit_code %s\n", msg);
	return(1); //temporary exitcodes. will be changed later
}

int	msh_clean(t_msh *msh, int err_out) //temporary function. might be changed later.
{
	(void) err_out;
	msh -> exit_code = EXIT_FAILURE;
	return(msh -> exit_code);
}

void print_envl(t_msh	*msh) //SUCCESS: unit test for envl duplication.
{
	while (*msh -> envl)
	{
		printf("%s\n", *msh -> envl);
		msh -> envl++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;
	(void) av;
	
	if (ac != 1)
		exit(err_out("# minishell: Error: Invalid number of arguments."
		"\n# Usage: ./minishell"));
	msh_init(&msh, envp);
	print_envl(&msh);
	msh_loop(&msh);
//	msh_clean(&msh, 1);
//	exit(msh.exit_code);
}
