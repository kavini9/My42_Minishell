/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_trailing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:50:10 by aoshinth          #+#    #+#             */
/*   Updated: 2025/05/31 19:30:51 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char concat_and_cleanup(t_mshmsh, char line, charadditional_input)
{
    char updated_input;

    // Concatenate the two input strings.
    updated_input = ft_strjoin(line, additional_input);
    free(additional_input); // Free the additional input string.

    msh->exit_code = 2;
    free(line); // Free the original input line.
    return (updated_input);
}

charget_trailing_input(t_msh msh, charline)
{
    char *additional_input=NULL;

    signal(SIGINT, sig_handler_heredoc);

    while (1)
    {
        additional_input = readline("> ");
        if (!additional_input || g_sig == SIGINT)
        {
            g_sig = 0;
            msh->exit_code = 2;
            free(additional_input);  // safe even if NULL
            free(line);
            return (NULL);
        }
        if (!is_input_empty(additional_input))
            return (concat_and_cleanup(msh, line, additional_input));
        free(additional_input);  // if input is empty, prompt again
    }
}