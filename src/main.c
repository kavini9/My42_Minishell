/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:28:31 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 12:34:50 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;

	(void) av;
	if (ac != 1)
		exit(printf("# minishell: Error: Invalid number of arguments."
				"\n# Usage: ./minishell"));
	msh_init(&msh, envp);
	msh_loop(&msh);
	msh_clean(&msh);
	exit(msh.exit_code);
}
