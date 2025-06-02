/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_trailing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:50:10 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/02 17:58:30 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *concat_and_cleanup(t_msh *msh, char *line, char *additional_input)
{
    char *updated_input;

    updated_input = ft_strjoin(line, additional_input);
    free(additional_input);
    free(line);
    msh->exit_code = 2;
    return (updated_input);
}

char *get_trailing_input(t_msh *msh, char *line)
{
    char *additional_input = NULL;

    signal(SIGINT, sig_handler_heredoc);
    while (1)
    {
        additional_input = readline("> ");
        if (!additional_input || g_sig == SIGINT)
        {
            g_sig = 0;
            msh->exit_code = 2;
            free(additional_input);
            free(line);
            return (NULL);
        }
        if (!is_input_empty(additional_input))
            return (concat_and_cleanup(msh, line, additional_input));
        free(additional_input);
    }
}