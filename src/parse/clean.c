/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:07:44 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/21 14:09:29 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * clean_cmds - Frees memory allocated for the command structures.
 *
 * This function iterates over the array of command structures (`cmds`) and frees
 * the memory allocated for each individual command's fields, including the command
 * name, command path, arguments, redirections, and the structure itself. It also
 * frees the array holding the command pointers. The function assumes that dynamic
 * memory for `cmd_args`, `redir_start`, and `redir_end` needs to be cleaned using
 * corresponding functions.
 *
 * @cmds: Pointer to the array of command structures to be cleaned up.
 */
void clean_cmds(t_cmd **cmds)
{
    int i;

    i = 0;
    while (cmds[i])
    {
        // Free `cmd_args` array (array of arguments passed to the command)
        ft_free_array(cmds[i]->cmd_args);
        
        // Free `cmd_name` and `cmd_path` if they were allocated
        if (cmds[i]->cmd_name != NULL)
            free(cmds[i]->cmd_name);
        if (cmds[i]->cmd_path != NULL && cmds[i]->cmd_path != cmds[i]->cmd_name)
            free(cmds[i]->cmd_path);
        
        // Free redirection pointers (assuming they need freeing)
        if (cmds[i]->redir_start)
            clean_redir(cmds[i]->redir_start);  // Assuming `clean_redir` handles redirection cleanup
        if (cmds[i]->redir_end)
            clean_redir(cmds[i]->redir_end);    // Same for redir_end

        // Free the command structure itself
        free(cmds[i]);
        i++;
    }

    // Free the array of command pointers and set it to NULL
    free(cmds);
    cmds = NULL;
}
