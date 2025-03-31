/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/31 13:55:44 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define  ERROR_MSG "minishell: Error" // represents a enum containing all the err codes for now.

# include <readline/readline.h> //for readline
# include <readline/history.h> //for readline add_history function
# include <stdio.h> //temporary printf in msh_clean. delete later if you use your own
# include <stdlib.h> //for exit
# include <string.h> //for strerror(errnum)
# include <errno.h> //for using errno in strerror

typedef enum e_do_err {
    LOG   = 0b001,
	CLEAN = 0b010,
	EXIT  = 0b100
} t_do_err;

typedef enum e_err_type{
	ERR_SYS_FUNC,
	ERR_MALLOC,
	
} t_err_type;

typedef struct s_msh
{
	int		cmd_count; //  for command.c
	char	*cwd;
	char	*old_wd;
	char	*prompt;
	char	**envl;
	t_token	**tokens;
	char	**envl;
	t_token	*tokenl;
	int		exit_code;
} t_msh;

# include "../lib/libft/libft.h"
# include "envp.h"
# include "../src/parse/parse.h"
//# include "execute.h"
//# include "builtin.h"
# include "../src/signal/signal.h"



// typedef struct s_env
// {
// 	char 	*var;
// 	char	*val;
// 	t_env	*next;
// } t_env;

void msh_init(t_msh *msh, char **envp);
void	msh_loop(t_msh *msh);
//void	msh_clean(t_msh *msh);
int err_out(char *msg);

#endif
