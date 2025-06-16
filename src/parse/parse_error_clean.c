/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:15:44 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/14 18:53:38 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void clean_aux(t_msh *msh, t_parse *aux)
{
    t_token **token;
    t_token *tok;
    
    // free(*aux -> line);//find a way to free line before exit
    //     *aux -> line = NULL;
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

void clean_exp(t_expan *exp)
{
    if (exp -> tok)
        free(exp -> tok);
    if (exp -> prefix)
        free(exp -> prefix);
    if (exp -> key)
        free(exp -> key);
    if (exp -> tmp_arr)
        free_arr((void **) exp -> tmp_arr);
    ft_memset(exp, 0, sizeof(t_expan));
}

void parse_error(t_msh *msh, t_parse *aux, t_expan *exp, char *func_name)
{
    printf_fd(STDERR_FILENO, ERR_MALLOC, func_name);
    clean_aux(msh, aux);
    if (exp)
        clean_exp(exp);
    msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, func_name);
}