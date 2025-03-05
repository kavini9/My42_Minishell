/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:32:56 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/05 22:28:37 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*prompt_gen(t_msh *msh)
{
	if(ft_strcmp(msh -> cwd, msh -> old_wd)
		       prompt_update(msh -> cwd);

}

void	minishell(t_msh *msh)
{
	char	*line;

	while(1)
	{
		line = readline(prompt_gen(msh));
	}
}


int	main(int ac, char **av, char **envp)
{
	t_msh	msh
	(void) av;
	
	if (ac != 1)
		exit(error("# minishell: Error: Invalid number of arguments."
		"\n# Usage: ./minishell", 2);
	msh_init(&msh, envp);
	minishell(&msh);
	msh_clean($msh);
	exit(msh.exitcode);
}
