/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_struct_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:32:19 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/03 22:50:30 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void revise_exp_arr(t_msh *msh, t_token *token, t_expan *exp)
{
    int exp_len;
    int tmp_len;
    int size;
    int new_exp_len;

    exp_len = token -> expn_len;
    size = sizeof(char *);
    tmp_len = ft_arrlen((void **) exp -> tmp_arr);
    if (!exp_len)//for new exp len we include NULL in the len.
        new_exp_len = tmp_len + 1;// when exp_len is zero in the initial expansion there won't be space for NULL terminator.
    else
        new_exp_len = exp_len + tmp_len;
    // if (!token->token)
    free(token -> token);//can this affect the memcpy.
    token -> expn = ft_realloc(token -> expn, exp_len * size , new_exp_len * size);// this needs refining
    if (!token -> expn)
        exit(printf("#!exp -> exp_arr minishell: Error:Malloc Fail.\n"));
    if (exp_len > 0)
    {
        // free(*((token -> expn) + exp_len - 1));//this was causing double free
        ft_memcpy((token -> expn) + exp_len - 1, exp -> tmp_arr, tmp_len * sizeof(char *));    
    }
    else
        ft_memcpy((token -> expn), exp -> tmp_arr, tmp_len * sizeof(char *));
    token -> expn_len = new_exp_len - 1;//when this -1 was added to when setting new exp len it did not work for realloc.
    free(exp -> prefix);
    token -> token = token -> expn[new_exp_len - 2];
    exp -> tok = token -> token;
    exp -> suffix = token -> token + exp -> scan_offset;
    exp -> prefix = ft_calloc(ft_strlen(token -> token), sizeof(char));
    if (!exp -> prefix)
        exit(printf("#!exp -> prefix minishell: Error:Malloc Fail%i\n", msh -> exit_code));// added exit code to avoidunused param error
    ft_memcpy(exp -> prefix, exp -> tok, exp -> scan_offset * sizeof(char));//we didn't do this before. thats wht the next element set did niot include the previous
    exp -> exp = exp -> prefix + exp -> scan_offset;
    free(exp -> key);
    exp -> key = NULL;
    free(exp -> tmp_arr);
    exp -> tmp_arr = NULL;
}

void init_exp(t_msh *msh, t_token token, t_expan *exp)//should I pass t_token *
{
    ft_memset(exp, 0, sizeof(t_expan));
    exp -> tok = token.token;//hope it doesn't matter parsing token by value cause the pointer pointing to token string will stil be the same number so it still points to the same block  
    exp -> suffix = token.token;
    exp -> prefix = ft_calloc(ft_strlen(token.token), sizeof(char));
    if (!exp -> prefix)
        exit(printf("# minishell: Error:Malloc Fail.%i\n", msh -> exit_code));// added exit code to avoidunused param error
    exp -> exp = exp -> prefix;
}