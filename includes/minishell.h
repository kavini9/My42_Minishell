/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/11 22:54:45 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define  ERROR_MSG "minishell: Error" // represents a enum containing all the err codes for now.

# include <readline/readline.h> //for readline
# include <readline/history.h> //for readline add_history function
# include <stdio.h> //temporary printf in msh_clean. delete later if you use your own
# include <stdlib.h> //for exit

# include "../lib/libft/libft.h"
# include "envp.h"
# include "parse.h"
# include "execute.h"
# include "builtin.h"
# include "signal.h"

typedef struct s_msh
{
	char	*cwd;
	char	*old_wd;
	char	*prompt;
	int		exit_code;
	char	**envl;
//	t_token	*tokenl;
} t_msh;

// typedef struct s_env
// {
// 	char 	*var;
// 	char	*val;
// 	t_env	*next;
// } t_env;

void msh_init(t_msh *msh, char **envp);
void	msh_loop(t_msh *msh);
int	msh_clean(t_msh *msh, int err_out);
int err_out(char *msg);

#endif
