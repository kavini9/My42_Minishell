/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:44:37 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/17 22:54:14 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Global signal indicator used across the shell.
 *
 * This variable is declared as volatile sig_atomic_t to safely store
 * asynchronous signal states (e.g., SIGINT) without risking race conditions.
 * It is only used in signal-safe contexts like heredoc interruption.
 */
volatile __sig_atomic_t g_sig = 0;

/**
 * @brief Set default signal handlers for main shell prompt.
 *
 * This is called after command execution or at shell startup.
 * - SIGINT is handled by `sigint_handler` to reset prompt on Ctrl+C.
 * - SIGQUIT is ignored (Ctrl+\ should have no effect in prompt).
 */
void	init_sig(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Set signal handlers before executing child processes.
 *
 * These handlers mimic bash's behavior during command execution.
 * - SIGINT (Ctrl+C): prints newline.
 * - SIGQUIT (Ctrl+\): prints "Quit (core dumped)".
 * Used after fork but before execve.
 */
void	sig_handler_changer(void)
{
	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, sig_handler_child);
}

/**
 * @brief Reset signal handlers to default.
 *
 * Called right before calling execve, so that the new program
 * receives normal system signal behavior.
 * - SIGINT → default
 * - SIGQUIT → default
 */
void	sig_reseted(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief Set signal handler for heredoc input mode.
 *
 * - SIGINT is handled by `sig_handler_heredoc` to cleanly exit heredoc.
 * - SIGQUIT is ignored to prevent abnormal termination.
 */
void	sig_heredoc(void)
{
	signal(SIGINT, sig_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
