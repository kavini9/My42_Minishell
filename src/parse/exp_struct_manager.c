/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_struct_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:32:19 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/11 16:32:31 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void update_exp_state(t_msh *msh, t_token *token, t_expan *exp)
{
    int index;
    //printf("111111111111111111111111111111: prefix before free: %s - %p\n", exp -> prefix, exp -> prefix);
    free(exp -> prefix);
    //printf("2222222222222222222222222222 token -> expn[token -> expn_len - 1] : %s - %i\n", token -> expn[token -> expn_len - 1], token -> expn_len - 1);
    if (token -> expn_len - 1 > 0)
        index = token -> expn_len - 1;
    else
        index = 0;
    exp -> tok = token -> expn[index];//prevviously this line was: exp -> tok = token -> expn[new_exp_len - 2]; changed to exp -> tok = token -> expn[new_exp_len - 1];
    //printf("333333333333333333333333333333: tok: %s - %p\n", exp -> tok, exp -> tok);
    exp -> suffix = exp -> tok + exp -> scan_offset;
    //printf("44444444444444444444444444444444: prefix: %s - %p\n", exp -> suffix, exp -> suffix);
    exp -> prefix = ft_calloc(ft_strlen(exp -> tok), sizeof(char));
    if (!exp -> prefix)
        exit(printf("# minishell: update_exp_state: Error:Malloc Fail.%i\n", msh -> exit_code));// added exit code to avoidunused param error
    ft_memcpy(exp -> prefix, exp -> tok, exp -> scan_offset * sizeof(char));//we didn't do this before. thats wht the next element set did niot include the previous
    //printf("55555555555555555555555555555555: prefix after revise: %s\n", exp -> prefix);
    exp -> exp = exp -> prefix + exp -> scan_offset;
    //printf("6666666666666666666666666666666: exp: %s\n", exp -> exp);
    free(exp -> key);
    exp -> key = NULL;
    free(exp -> tmp_arr);
    exp -> tmp_arr = NULL;
    exp -> scan_offset = 0;
}

// static void print_array(char **arr)
// {
//     char **tmp = arr;
//     //printf("00000000000000000000000000000000000000: expn: %p\n", arr);
//     while(*tmp)
//     {
//         printf("arr: %s\n", *tmp);
//         tmp++;
//     }
// }

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
    token -> expn = ft_realloc(token -> expn, exp_len * size , new_exp_len * size);// this needs refining
    if (!token -> expn)
        exit(printf("# minishell: revise_exp_arr: Error:Malloc Fail.\n"));
    if (exp_len > 0)
    {
        free(*((token -> expn) + exp_len - 1));//this was causing double free but now okay
        ft_memcpy((token -> expn) + exp_len - 1, exp -> tmp_arr, tmp_len * sizeof(char *));    
    }
    else
        ft_memcpy((token -> expn), exp -> tmp_arr, tmp_len * sizeof(char *));
    //printf("00000000000000000000000000000000000000: expn: %p\n", token -> expn);
    //print_array(token -> expn);
    token -> expn_len = new_exp_len - 1;//when this -1 was added to when setting new exp len it did not work for realloc.
    update_exp_state(msh, token, exp);
}

void init_exp(t_msh *msh, t_token token, t_expan *exp)//should I pass t_token *
{
    ft_memset(exp, 0, sizeof(t_expan));
    exp -> tok = token.token;//hope it doesn't matter parsing token by value cause the pointer pointing to token string will stil be the same number so it still points to the same block  
    exp -> suffix = token.token;
    exp -> prefix = ft_calloc(ft_strlen(token.token), sizeof(char));
    if (!exp -> prefix)
        exit(printf("# minishell: init_exp: Error:Malloc Fail.%i\n", msh -> exit_code));// added exit code to avoidunused param error
    exp -> exp = exp -> prefix;
}