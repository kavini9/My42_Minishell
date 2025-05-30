/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/29 22:35:45 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"

void expand_and_setup_cmd(t_msh *msh, t_token **token);
void expscan_token(t_msh *msh, t_token token);
void expscan_token(t_msh *msh, t_token token);
char *extract_env_key(char **token);
void init_exp(t_msh *msh, t_token token, t_expan *exp);

void init_exp(t_msh *msh, t_token token, t_expan *exp)
{
    ft_memset(exp, 0, sizeof(t_expan));
    exp -> tok = token.token;
    exp -> suffix = token.token;
    exp -> prefix = ft_calloc(ft_strlen(token.token), sizeof(char));
    if (!exp -> prefix)
        exit(printf("# minishell: Error:Malloc Fail.\n"));
    exp -> exp = exp -> prefix;
}

char *extract_env_key(char **token)
{
    char *start;
    int var_len;
    
    var_len = 0;
    (*token)++;
    start = *token;
    while (ft_isalnum(**token) || **token == '_' || **token == '?' )
    {
        if (var_len == 0 || **token != '?')
            var_len++;
        (*token)++;
        if ((start == *token - 1 && ft_isdigit(*(*token - 1))) 
        || *(*token - 1) == '?')
            break;
    }
    return (ft_substr(start, 0, var_len));
}

void    get_tmp_arr(t_msh *msh, t_expan *exp, char *exp_dup, int q_context)
{
    char *tmp_exp_dup;
    
    if (*exp_dup && !q_context)
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
        exit(printf("# minishell: Error:Malloc Fail.\n"));
}

size_t	ft_arrlen(void **arr)
{
	size_t	len;

	len = 0;
	while (*arr++)
		len++;
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
        exit(printf("# minishell: Error:Malloc Fail.\n"));
    free((exp -> tmp_arr[index]));
    exp -> tmp_arr[index] = tmp;
}

void    extend_exp_edge(t_msh *msh, t_expan *exp, int index, int *len)
{
    exp -> tmp_arr = ft_realloc(exp -> tmp_arr, len , len + 1);
    if (!exp -> tmp_arr)
        exit(printf("# minishell: Error:Malloc Fail.\n"));
    if (index == 0)
    {
        ft_memmove(exp -> tmp_arr, exp -> tmp_arr + 1, len * sizeof(char *));
        exp -> tmp_arr[index] = ft_strdup(exp -> prefix);
    }
    else
    {
        exp -> tmp_arr[index] = ft_strdup(exp -> suffix);
        exp -> tmp_arr[index + 1] = NULL;
    }
    if (!exp -> tmp_arr[index])
        exit(printf("# minishell: Error:Malloc Fail.\n"));
    (*len)++;
}

void    fix_exp_edge(t_msh *msh, t_expan *exp, char *exp_val, int q_context)
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

void    expand_parameter(t_msh *msh, t_expan *exp)
{
    char    *exp_val;
    char    *exp_dup;
    int q_context;

    q_context = check_quotes(exp -> exp, exp -> prefix);
    exp_val = get_env(msh -> envl, exp -> key);//this needs to be replaced to get ? $$
    if (exp_val)
        exp_dup = ft_strdup(exp_val);
    else
        exp_dup = ft_strdup("");
    if (!exp_dup)
        exit(printf("# minishell: Error:Malloc Fail.\n"));
    get_tmp_arr(msh, exp, exp_dup, q_context);
    fix_exp_edge(msh, exp, exp_val, q_context);
}

void expscan_token(t_msh *msh, t_token token)
{
    t_expan exp;

    init_exp(msh, token, &exp);
    while (*exp.suffix)
    {
        printf("exp.suffix: %s\n", exp.suffix);
        if (*(exp.suffix) == '$' && check_quotes(exp.tok, exp.suffix) != '\'')
        { //do we need siffix + 1. why do I do that in test_parse
            exp.key = extract_env_key(&(exp.suffix));
            if (!exp.key)
                exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC //  have to free exp.prefix.
            printf("key: %s\nexp.suffix: %s\n", exp.key, exp.suffix);
            expand_parameter(msh, &exp);
        }     
        ft_memcpy(exp.exp, exp.suffix, sizeof(char));
        printf("exp.exp: %s\n", exp.exp);
        exp.suffix++;
        exp.exp++;
    }
}

void expand_and_setup_cmd(t_msh *msh, t_token **token)
{
    char *token_iter;

    while (*token)
    {
        while ((**token).token)
        {
            printf("printing tokens in expand: %s\n", (**token).token);
            token_iter = ft_strchr((**token).token, '$');
            printf("printing token_iter in expand: %s\n", token_iter);
            while (token_iter && *token_iter && check_quotes((**token).token, token_iter) == '\'')//we removed token_iter + 1 in check quotes.
                token_iter = ft_strchr((++token_iter), '$');
            if (token_iter)
                expscan_token(msh, **token);
            (*token)++;
        }
        token++;
    }
}

// if the expansion is within the "" the field splitting is not applied to the expanded output. otherwise split it with the spaces.

//walk through the string while removing quotes
//save what was the last quote type
//when found $ sign pass it to find key 
//when the key is found pass it to expand with quoted or unquoted flag.
//create a array with the
//tilde expansion should be done after variable expansion because variables can include tilde.

//check quotes in the split pipe can be redundant if we can use a flag for it.
//But flag will also have to be introduced to everywhere we have to check quote context.
//So keep it for now.

//if a export varaibe consist of a $ it should be expanded before adding to the env. 