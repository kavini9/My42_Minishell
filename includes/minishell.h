/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/15 18:13:30 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define  ERROR_MSG "minishell: Error" // represents a enum containing all the err codes for now.
# define  HEREDOC_MAX 16

#include <signal.h>
# include <readline/readline.h> //for readline
# include <readline/history.h> //for readline add_history function
# include <stdio.h> //temporary printf in msh_clean. delete later if you use your own
# include <stdlib.h> //for exit
# include <string.h> //for strerror(errnum)
# include <errno.h> //for using errno in strerror
# include <unistd.h>//for fork
# include <sys/types.h>//for pid_t
# include <fcntl.h>//for file open flags
# include <stdbool.h>
# include <stddef.h>

extern volatile __sig_atomic_t g_sig;

typedef enum e_do_err {
    LOG   = 0b001,
	CLEAN = 0b010,
	EXIT  = 0b100
} t_do_err;

typedef enum e_err_type{
	ERR_SYS_FUNC,
	ERR_MALLOC,
} t_err_type;


/* typedef struct s_msh
{
	char	*cwd;
	char	*old_wd;
	char	*prompt;
	char	**envl;
	t_cmd	*cmd;
	int		cmd_count; //  for command.c
	int		hdocfd_l[HEREDOC_MAX];
	int		exit_code;
} t_msh; */


# include "../lib/libft/libft.h"
# include "signal_utils.h"
# include "parse.h"
# include "envp.h"
# include "execute.h"
# include "builtin.h"


/* void msh_init(t_msh *msh, char **envp);
void	msh_loop(t_msh *msh);
//void	msh_clean(t_msh *msh);
int err_out(char *msg); */

#endif