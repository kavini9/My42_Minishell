/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:15:44 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/09 21:13:38 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void clean_aux(t_msh *msh, t_parse *aux)
{
    t_token **token;
    t_token *tok;
    
    free_arr((void **) aux -> seg);
    token = aux -> token;
    while (*token)
    {
        tok = *token;
        while (tok -> token)
        {
            if (tok -> token)
                free(tok -> token);
            if (tok-> expn)
                free_arr((void **) tok -> expn);
            tok++;
        }
        free(*token);
        token++;
    }
    free(aux -> token);
    msh -> aux = NULL;
}