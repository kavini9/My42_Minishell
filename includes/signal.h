#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"

extern int g_sig; // Declare the global signal variable.
//extern volatile sig_atomic_t g_sig;

/* Signal Handling Initialization */
void init_sig(void);
void sig_handler_changer(void);
void sig_reseted(void);
void sig_heredoc(void);

/* Signal Handlers */
void sigint_handler(int sig);
void sig_handler2(int sig);
void sig_handler_heredoc(int signum);
void sig_handler_hd(int signal);

#endif /* SIGNAL_HANDLER_H */
