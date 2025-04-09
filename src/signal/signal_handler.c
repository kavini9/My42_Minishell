/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:44:37 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/04 16:32:01 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Global signal indicator used across the shell.
 * 
 * This variable stores only the signal number received by the shell.
 * It is marked `volatile sig_atomic_t` to ensure safe access across
 * asynchronous signal handlers and the main shell loop.
 *
 * This is the **only global variable** allowed to interact with signals,
 * complying with the requirement to keep handlers isolated from the shell state.
 */

volatile sig_atomic_t g_sig = 0;  // Global signal indicator, safe for use in handlers.

/**
 * @brief Initializes signal handling for the main shell prompt.
 * 
 * Called at shell startup or before displaying a prompt, this sets:
 * - SIGINT to `sigint_handler` to allow Ctrl+C to reset the prompt.
 * - SIGQUIT to SIG_IGN to ignore Ctrl+\ (which otherwise causes core dumps).
 */
void	init_sig(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Updates signal handlers before executing child processes.
 * 
 * This setup ensures the child process (created by fork) receives proper signal
 * handling:
 * - SIGINT and SIGQUIT are passed to `sig_handler_child`, allowing meaningful
 *   output and tracking of termination signals.
 * 
 * Called right after fork but before `execve`.
 */
void	sig_handler_changer(void)
{
	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, sig_handler_child);
}

/**
 * @brief Resets signal handling to system defaults.
 * 
 * Called just before `execve()` to ensure the new program inherits default
 * OS signal behavior.
 * 
 * - SIGINT → SIG_DFL
 * - SIGQUIT → SIG_DFL
 * 
 * Prevents shell-specific behavior from leaking into external commands.
 */
void	sig_reseted(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief Configures signal handling specifically for heredoc mode.
 * 
 * Used when the shell is reading heredoc input (i.e., `<<` operator).
 * 
 * - SIGINT is set to `sig_handler_heredoc` to allow interruption.
 * - SIGQUIT is ignored (to avoid crashes or abnormal exits).
 */
void	sig_heredoc(void)
{
	signal(SIGINT, sig_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}