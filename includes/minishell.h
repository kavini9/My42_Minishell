/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/04 14:48:10 by aoshinth         ###   ########.fr       */
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
	t_cmd	**cmds;
	t_cmd	*cmd;
	int		exit_code;
} t_msh;

# include "../lib/libft/libft.h"
# include "envp.h"
# include "parse.h"
//# include "execute.h"
//# include "builtin.h"
# include "signal.h"



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