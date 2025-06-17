/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:43:19 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/18 00:08:05 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Signal handler for SIGINT (Ctrl+C) in the main shell prompt.
 * 
 * When a user presses Ctrl+C at the shell prompt, this function clears the
 * current input line and redisplays the prompt without exiting the shell.
 */
void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = sig;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @brief Signal handler for SIGINT and SIGQUIT during child process execution.
 * 
 * This function handles output for these signals and updates the global `g_sig`
 * for the parent to evaluate proper exit code.
 */
void sig_handler_child(int sig)
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
 * This allows the heredoc process to exit gracefully without crashing.
 */
void sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = signum;
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		close(STDIN_FILENO);
	}
}

