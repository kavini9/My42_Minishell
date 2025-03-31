/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/28 17:03:40 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**
 * @file minishell.h
 * @brief Central header for global shell structures and includes.
 *
 * Defines the main shell structure (`t_msh`), includes project-wide headers,
 * and declares core shell functions like init, loop, and cleanup.
 */

# define ERROR_MSG "minishell: Error"

# include <readline/readline.h>   // For input line handling
# include <readline/history.h>    // For command history support
# include <stdio.h>               // For debugging (e.g., printf)
# include <stdlib.h>              // For malloc, free, exit
# include <string.h>              // For strerror, memcpy
# include <errno.h>               // For errno and error messages

/* ────────────────────────────────────────────────────────────── */
/*                      CUSTOM HEADERS                            */
/* ────────────────────────────────────────────────────────────── */

# include "../lib/libft/libft.h"
# include "envp.h"
# include "../src/parse/parse.h"
# include "../src/signal/signal.h"
// # include "execute.h"  // Uncomment when execution is implemented
// # include "builtin.h"  // Uncomment when builtins are implemented

/* ────────────────────────────────────────────────────────────── */
/*                         STRUCTURES                             */
/* ────────────────────────────────────────────────────────────── */

/**
 * @struct s_msh
 * @brief Core shell state structure.
 *
 * Stores the current state of the shell, including environment,
 * prompt, and parsed command tokens.
 *
 * @cmd_count: Number of parsed commands (pipe segments).
 * @cwd: Current working directory.
 * @old_wd: Previous working directory.
 * @prompt: Prompt string to be displayed.
 * @envl: Environment variable list (NULL-terminated).
 * @tokens: Parsed command tokens (array of pointers).
 * @exit_code: Last command exit code (used for $?).
 */
typedef struct s_msh
{
	int			cmd_count;
	char		*cwd;
	char		*old_wd;
	char		*prompt;
	char		**envl;
	t_token		**tokens;
	int			exit_code;
}	t_msh;

/* ────────────────────────────────────────────────────────────── */
/*                    CORE SHELL FUNCTIONS                        */
/* ────────────────────────────────────────────────────────────── */

/**
 * @brief Initializes the shell state (allocates structures, sets env).
 * 
 * @param msh Pointer to the shell structure.
 * @param envp Environment from main().
 */
void	msh_init(t_msh *msh, char **envp);

/**
 * @brief The main shell loop handling input and execution.
 *
 * @param msh Pointer to the initialized shell structure.
 */
void	msh_loop(t_msh *msh);

/**
 * @brief Cleans up allocated memory and exits the shell.
 *
 * @param msh Pointer to the shell structure.
 * @param err_out If non-zero, returns an error status.
 * @return Exit code to return from main.
 */
int		msh_clean(t_msh *msh, int err_out);

/**
 * @brief Handles error output and returns error code.
 *
 * @param msg Error message to display.
 * @return Always returns 1.
 */
int		err_out(char *msg);

#endif // MINISHELL_H
