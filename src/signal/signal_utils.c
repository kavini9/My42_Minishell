/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:43:19 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/04 16:31:47 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Signal handler for SIGINT (Ctrl+C) in the main shell prompt.
 * 
 * When a user presses Ctrl+C at the shell prompt, this function clears the
 * current input line and redisplays the prompt without exiting the shell.
 * 
 * Behavior:
 * - Clears the current line (via readline).
 * - Prints a newline.
 * - Displays a fresh prompt.
 *
 * @param sig The received signal number (expected: SIGINT).
 */
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @brief Signal handler for SIGINT and SIGQUIT during child process execution.
 * 
 * This function is set before the shell forks a child process to execute a command.
 * It reflects expected shell behavior (like bash):
 * 
 * - SIGINT: prints a newline to allow clean interrupt.
 * - SIGQUIT: prints "Quit (core dumped)" to stderr.
 * 
 * In both cases, the received signal is stored in the global `g_sig` for the
 * parent process to later analyze how the child terminated.
 *
 * @param sig The received signal number (SIGINT or SIGQUIT).
 */
void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	g_sig = sig;
}

/**
 * @brief Signal handler for SIGINT (Ctrl+C) during heredoc input mode.
 * 
 * When the shell is reading heredoc input (e.g., via `<<`), this function
 * is used to safely interrupt heredoc processing:
 * 
 * - Sets the global `g_sig` variable to SIGINT.
 * - Clears the current input line and resets prompt.
 *
 * This allows the heredoc process to exit gracefully without crashing.
 * 
 * @param signum The received signal number (expected: SIGINT).
 */
void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = signum;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}