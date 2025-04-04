#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"

extern volatile sig_atomic_t g_sig;

void	sigint_handler(int sig);
void	sig_handler_child(int sig);
void	sig_handler_heredoc(int signum);
void	init_sig(void);
void	sig_handler_changer(void);
void	sig_reseted(void);
void	sig_heredoc(void);

#endif
