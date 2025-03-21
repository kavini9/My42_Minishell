/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:43:19 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/21 14:40:56 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C) during the main shell prompt.
 *
 * This function allows the user to interrupt their input without exiting the shell.
 * When SIGINT is received, it clears the current input line, moves to a new line, 
 * and redisplays the shell prompt. This provides the user with an opportunity to 
 * cancel their current input and begin a new line of input without terminating the shell.
 *
 * @sig: Signal number (expected to be SIGINT).
 */
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);  // Clears the current input line.
		printf("\n");             // Prints a newline to cleanly move to the next line.
		rl_on_new_line();        // Moves to a new line for the prompt.
		rl_redisplay();          // Redisplays the prompt on the new line.
	}
}

/**
 * sig_handler2 - Handles both SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) signals for child processes.
 *
 * This function is responsible for ensuring that child processes react appropriately
 * to the SIGINT and SIGQUIT signals. For SIGINT, it simply prints a newline, allowing
 * the child process to terminate gracefully. For SIGQUIT, it prints the message 
 * "Quit (core dumped)" to standard error to inform the user of the process' abnormal termination.
 *
 * @sig: Signal number (either SIGINT or SIGQUIT).
 */
void	sig_handler2(int sig)
{
	if (sig == SIGINT)
		printf("\n");  // Prints a newline when SIGINT is received.
	if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);  // Prints the "Quit" message for SIGQUIT.
}

/**
 * sig_handler_heredoc - Handles SIGINT (Ctrl+C) during heredoc input mode.
 *
 * This function specifically handles the SIGINT signal when the user is interacting
 * with a heredoc input. When SIGINT is received, it updates the global `g_sig` variable
 * to record that SIGINT was received, clears the current heredoc input line, moves to a new line, 
 * and redisplays the prompt to allow the user to handle the interruption and decide what to do next.
 *
 * @signum: Signal number (expected to be SIGINT).
 */
void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = signum;  // Updates the global variable to indicate SIGINT was received.
		rl_replace_line("", 0);  // Clears the current input line.
		rl_on_new_line();        // Moves to a new line.
		rl_redisplay();          // Redisplays the prompt on the new line.
	}
}

