/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_array_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/05 00:38:38 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

size_t	ft_arrlen(void **arr)
{
	size_t	len;

	len = 0;
	while (*arr)
    {
		len++;
        arr++;
    }
	return (len);
}

void    concat_exp_edge(t_msh *msh, t_expan *exp, int spc, int index)
{
    char *tmp;

    if (spc == 0)
        tmp = ft_strjoin(exp -> prefix, exp -> tmp_arr[index]);
    else
    {
        exp -> scan_offset = ft_strlen(exp -> tmp_arr[index]);
        tmp = ft_strjoin(exp -> tmp_arr[index], exp -> suffix);
    }
    if (!tmp)
        exit(printf("#!tmp minishell: Error:Malloc Fail%i\n", msh -> exit_code));// added exit code to avoidunused param error
    printf("concat_exp_edge: tmp : %s\n", tmp);
    free((exp -> tmp_arr[index]));
    exp -> tmp_arr[index] = tmp;
}

//index is the 0 when called for handling leading space 
//index is (arr_len - 1) when called for handling trailing space
/*
This function is is used to add a extra element to the front or end of the tmp_arr 
and fill it with prefix or suffix respectively.
*/
void    extend_exp_edge(t_msh *msh, t_expan *exp, int index, int *len)
{
    exp -> tmp_arr = ft_realloc(exp -> tmp_arr, (*len + 1) * sizeof(char *), (*len + 2) * sizeof(char *));
    if (!exp -> tmp_arr)
        exit(printf("#!exp -> tmp_arr minishell: Error:Malloc Fail%i\n", msh -> exit_code));// added exit code to avoidunused param error
    if (index == 0)
    {
        ft_memmove(exp -> tmp_arr + 1, exp -> tmp_arr, (*len) * sizeof(char *));
        *(exp -> tmp_arr) = strdup(exp -> prefix);
    }
    else
    {
        exp -> tmp_arr[index] = ft_strdup(exp -> suffix);
        exp -> tmp_arr[index + 1] = NULL;
    }
    if (!exp -> tmp_arr[index])
        exit(printf("#!exp -> tmp_arr[index] minishell: Error:Malloc Fail.\n"));
    (*len)++;
}
//print array block
    // char **tmp = exp -> tmp_arr;
    // int c = 0;
    // while(*tmp[c])
    // {
    //     printf("extend_exp_edge: exp -> tmp_arr[%i] : %s\n", c,  exp -> tmp_arr[c]);
    //     c++;
    // }

void    adjust_exp_edge(t_msh *msh, t_expan *exp, char *exp_val, int q_context)
{
    int lead_spc;
    int trail_spc;
    int len;

    len = 0;
    lead_spc = 0;
    trail_spc = 0;
    if (exp_val)
        len = ft_strlen(exp_val);
    if (len > 0 && !q_context)
    {
        lead_spc = (ft_strchr(" \t\n\r\f\v", exp_val[0]) != NULL);
        trail_spc = (ft_strchr(" \t\n\r\f\v", exp_val[len - 1]) != NULL);//check if index is correct
    }
    len = ft_arrlen((void **) exp -> tmp_arr);
    if (!lead_spc)
        concat_exp_edge(msh, exp, 0, 0);
    else
        extend_exp_edge(msh, exp, 0, &len);
    if (!trail_spc)
        concat_exp_edge(msh, exp, len, len - 1);
    else
        extend_exp_edge(msh, exp, len, &len);
}

void    get_tmp_arr(t_msh *msh, t_expan *exp, char *exp_dup, int quote_or_redir)
{
    char *tmp_exp_dup;
    
    if (*exp_dup && !quote_or_redir)
    {
        tmp_exp_dup = exp_dup;
        while (*tmp_exp_dup)
        {
            if (ft_strchr("\t\n\r\f\v", *tmp_exp_dup))
                *tmp_exp_dup = ' ';
            tmp_exp_dup++;
        }
        exp -> tmp_arr = ft_split(exp_dup, ' ');
        free(exp_dup);//see if this is appropriate. in else case we assign it to the array so we need to keep it. but here we have a brand new array. so no need of exp_dup.
    }
    else
    {
        exp -> tmp_arr = ft_calloc(2, sizeof(char *));
        if (exp -> tmp_arr)
            *(exp -> tmp_arr) = exp_dup;
        else
            free(exp_dup); //if array creation failed we will loose exp_dup because it is not in our struct
    }
    if (!exp -> tmp_arr)
        exit(printf("#!exp -> tmp_arr minishell: Error:Malloc Fail%i\n", msh -> exit_code));// added exit code to avoidunused param error
}

