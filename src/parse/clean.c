/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:07:44 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/26 12:35:05 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * clean_tokens - Frees memory allocated for an array of token structures.
 *
 * @tokens: Pointer to an array of token structures.
 *
 * Iterates through the array of token structures, freeing all dynamically allocated
 * memory, including token arguments, token names, token paths, and redirection
 * structures. Finally, frees the token array itself.
 */
void clean_tokens(t_token **tokens)
{
    int i;

    if (!tokens)
        return;

    i = 0;
    while (tokens[i])
    {
        // Free token arguments
        ft_free_array(tokens[i]->token_args);

        // Free command string and path
        if (tokens[i]->command)
            free(tokens[i]->command);
        if (tokens[i]->command_path && tokens[i]->command_path != tokens[i]->command)
            free(tokens[i]->command_path);

        // Free redirection structures
        if (tokens[i]->redir_start)
            clean_redir(tokens[i]->redir_start);
        if (tokens[i]->redir_end)
            clean_redir(tokens[i]->redir_end);

        // Free the token structure itself
        free(tokens[i]);
        i++;
    }

    // Free the token array itself
    free(tokens);
}
