/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:07:44 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/24 14:06:01 by aoshinth         ###   ########.fr       */
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
 * structures. Finally, frees the token array itself and sets it to NULL to avoid 
 * dangling pointers.
 */
void clean_tokens(t_token **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        // Free `token_args` array (array of arguments passed to the token)
        ft_free_array(tokens[i]->token_args);

        // Free `token_name` and `token_path` if they were allocated
        if (tokens[i]->token_name != NULL)
            free(tokens[i]->token_name);
        if (tokens[i]->token_path != NULL && tokens[i]->token_path != tokens[i]->token_name)
            free(tokens[i]->token_path);

        // Free redirection pointers (assuming they need freeing)
        if (tokens[i]->redir_start)
            clean_redir(tokens[i]->redir_start);  // Assuming `clean_redir` handles redirection cleanup
        if (tokens[i]->redir_end)
            clean_redir(tokens[i]->redir_end);    // Same for redir_end

        // Free the token structure itself
        free(tokens[i]);
        i++;
    }

    // Free the array of token pointers and set it to NULL
    free(tokens);
    tokens = NULL;
}


