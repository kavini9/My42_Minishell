/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:32:56 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/11 00:00:58 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

// char	*prompt_gen(t_msh *msh)
// {
// 	if(ft_strcmp(msh -> cwd, msh -> old_wd)
// 		msh -> prompt = prompt_update(msh -> cwd);
// 	return(msh -> prompt)
// }

void msh_init(t_msh *msh, char **envp)
{
	ft_memset(msh, 0, sizeof(t_msh)); //set everything to NULL
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
	{
		perror("minishell: getcwd");
		exit(msh_clean(msh));//TODO: set the proper exit procedure. This is not correct.
	}
	msh -> old_wd = ft_strdup(msh -> cwd);
	if (!msh -> old_wd)
	{
		err_out("minishell: ft_strdup: malloc fail.");
		exit(msh_clean(msh));//TODO: set the proper exit procedure. This is not correct.
	}
	get_envl(msh, envp);
}

void	minishell(t_msh *msh)
{
	char	*line;

	while(1)
	{
		line = readline("minishell> ");
		if (*line)
		{
			add_history(line);
			printf("line entered: %s\n", line);
			msh_parse(msh, line);//parse and tokenize and add the list of tokens to msh -> token.
		}
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;
	(void) av;
	
	if (ac != 1)
		exit(msh_error("# minishell: Error: Invalid number of arguments."
		"\n# Usage: ./minishell", 2));
	msh_init(&msh, envp);
	minishell(&msh);
	msh_clean(&msh);
	exit(msh.exit_code);
}
