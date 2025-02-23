/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:21:34 by wweerasi          #+#    #+#             */
/*   Updated: 2025/01/21 17:13:57 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ft_strcmp(av[1], "here_doc") == 0 && ac <= 5)
	{
		ft_putendl_fd("# Output: Error: Invalid number of arguments."
			"\n# Usage: ./pipex_bonus here_doc LIMITER cmd1 cmd2 "
			"file", 2);
		exit(EXIT_FAILURE);
	}
	else if (ac < 5)
	{
		ft_putendl_fd("# Output: Error: Invalid number of arguments."
			"\n# Usage: ./pipex_bonus file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}	
	pipex_init(&pipex, ac, av, envp);
	ft_pipex(&pipex);
	exit(pipex.status);
}
