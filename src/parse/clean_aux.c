/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:15:44 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/09 20:14:33 by wweerasi         ###   ########.fr       */
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
        while ((*token) -> token)
        {
            if ((*token)-> token)
                free((*token)-> token);
            if ((*token)-> expn)
                free_arr((void **) (*token)-> expn);
            (*token)++;
        }
        free(tok);
        token++;
    }
    msh -> aux = NULL;
    printf("\n");
}