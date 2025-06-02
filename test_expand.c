/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/03 00:48:53 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitest.h"

void free_arr(char **arr)
{
    char **tmp;

    tmp = arr;
    while (*tmp)
    {
        free(*tmp);
        tmp++;
    }
    free(arr);
}

void init_exp(t_msh *msh, t_token token, t_expan *exp)//should I pass t_token *
{
    ft_memset(exp, 0, sizeof(t_expan));
    exp -> tok = token.token;//hope it doesn't matter parsing token by value cause the pointer pointing to token string will stil be the same number so it still points to the same block  
    exp -> suffix = token.token;
    exp -> prefix = ft_calloc(ft_strlen(token.token), sizeof(char));
    if (!exp -> prefix)
        exit(printf("# minishell: Error:Malloc Fail.\n"));
    exp -> exp = exp -> prefix;
}

void revise_exp_arr(t_msh *msh, t_token *token, t_expan *exp)
{
    int exp_len;
    int tmp_len;
    int size;
    int new_exp_len;
    
    exp_len = token -> expn_len;
    size = sizeof(char *);
    tmp_len = ft_arrlen((void **) exp -> tmp_arr);
    if (!exp_len)
        new_exp_len = tmp_len + 1;// when exp_len is zero in the initial expansion there won't be space for NULL terminator.
    else
        new_exp_len = exp_len + tmp_len;
    free(token -> token);//can this affect the memcpy.
    token -> expn = ft_realloc(token -> expn, (exp_len) * size , new_exp_len * size);// this needs refining
    if (!token -> expn)
        exit(printf("#!exp -> exp_arr minishell: Error:Malloc Fail.\n"));

    if (exp_len > 0)
    {
        free(*((token -> expn) + exp_len - 1));
        ft_memcpy((token -> expn) + exp_len - 1, exp -> tmp_arr, tmp_len * sizeof(char *));
    }
    else
        ft_memcpy((token -> expn) + exp_len, exp -> tmp_arr, tmp_len * sizeof(char *));
    token -> expn_len = new_exp_len;
    free(exp -> prefix);
    token -> token = token -> expn[new_exp_len - 2];
    exp -> tok = token -> token;
    exp -> suffix = token -> token + exp -> scan_offset;
    // char **print = token -> expn;//testing
    // printf("printing exp array\n");
    // while (*print)
    // {
    //     printf_fd(1, "[%s]\n", *print );
    //     print++;
    // }
    exp -> prefix = ft_calloc(ft_strlen(token -> token) - exp -> scan_offset, sizeof(char));
    if (!exp -> prefix)
        exit(printf("#!exp -> prefix minishell: Error:Malloc Fail.\n"));
    exp -> exp = exp -> prefix;
    free(exp -> key);
    exp -> key = NULL;
    free(exp -> tmp_arr);
    exp -> tmp_arr = NULL;
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
        exit(printf("#!exp -> tmp_arr minishell: Error:Malloc Fail.\n"));
}

size_t	ft_arrlen(void **arr)
{
	size_t	len;

    //printf("ft_arrlen\n");
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
        exit(printf("#!tmp minishell: Error:Malloc Fail.\n"));
    free((exp -> tmp_arr[index]));
    exp -> tmp_arr[index] = tmp;
}

void    extend_exp_edge(t_msh *msh, t_expan *exp, int index, int *len)
{
    exp -> tmp_arr = ft_realloc(exp -> tmp_arr, *len , *len + 1);
    if (!exp -> tmp_arr)
        exit(printf("#!exp -> tmp_arr minishell: Error:Malloc Fail.\n"));
    if (index == 0)
    {
        ft_memmove(exp -> tmp_arr, exp -> tmp_arr + 1, *len * sizeof(char *));
        exp -> tmp_arr[index] = ft_strdup(exp -> prefix);
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

static char *get_env(void)
{
    return(ft_strdup("test1     test2       test3"));
}

void    expand_parameter(t_msh *msh, t_token *token, t_expan *exp)
{
    char    *exp_val;
    char    *exp_dup;
    int q_context;

    q_context = check_quotes(exp -> exp, exp -> prefix);
    exp_val = get_env();//get_env(msh -> envl, exp -> key);//this needs to be replaced to get $? $$
    if (exp_val)
        exp_dup = ft_strdup(exp_val);
    else
        exp_dup = ft_strdup("");
    if (!exp_dup)
        exit(printf("#exp_dup minishell: Error:Malloc Fail.\n"));
    get_tmp_arr(msh, exp, exp_dup, q_context);
    adjust_exp_edge(msh, exp, exp_val, q_context);
    revise_exp_arr(msh, token, exp);
}

void expscan_token(t_msh *msh, t_token *token)
{
    t_expan exp;
    char **print;

    init_exp(msh, *token, &exp);
    while (*exp.suffix)
    {
        printf("exp.suffix: %s\n", exp.suffix);
        if (*(exp.suffix) == '$' && check_quotes(exp.tok, exp.suffix) != '\'')
        { //do we need suffix + 1. why do I do that in test_parse
            exp.key = extract_env_key(&(exp.suffix));
            if (!exp.key)
                exit(printf("# exp.key minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC //  have to free exp.prefix.
            printf("key: %s\nexp.suffix: %s\n", exp.key, exp.suffix);
            if (*exp.key)//this is for when we have something like $%
            {
                expand_parameter(msh, token, &exp);
                print = token -> expn;//testing
                printf("printing exp array\n");
                while (*print)
                {
                    printf_fd(1, "[%s]\n", *print );
                    print++;
                }
                printf_fd(1, "[%s]\n", *(print) );
            }
            else 
                exp.suffix--;//to copy the $ to the string. $ will be incremented after the if condition.
            printf("returned from expand parameter\n");
        }
        // printf("in a loop: exp.prefix: %s\n", exp.prefix);
        // printf("in a loop:exp.suffix: %s\n", exp.suffix);
        // printf("in a loop:exp.exp: %s\n", exp.exp);
        if (*exp.suffix)
        {
            ft_memcpy(exp.exp, exp.suffix, sizeof(char));
            exp.suffix++;
            exp.exp++;
        }
    }
    /*
    print = token -> expn;//testing
    printf("printing exp array\n");
    while (*print)
    {
        printf("[%s]\n", *print );
        print++;
    }
    */
}

void expand_tokens(t_msh *msh, t_token **token)
{
    char *token_iter;
    t_token *tok_tmp;

    while (*token)
    {
        tok_tmp = *token;
        while ((*tok_tmp).token)//use 
        {
            printf("printing tokens in expand: %s\n", (*tok_tmp).token);
            token_iter = ft_strchr((*tok_tmp).token, '$');
            printf("printing token_iter in expand: %s\n", token_iter);
            // while (token_iter && *token_iter && check_quotes((**token).token, token_iter) == '\'')//we removed token_iter + 1 in check quotes.
            //     token_iter = ft_strchr((++token_iter), '$');//this part was added because I checked the availability of the tilde here as well may be we dont need it here just add the condition check quotes in if
            printf("here, token_iter: START%sEND\n", token_iter);
            if ((*tok_tmp).redir != REDIR_HDOC && token_iter 
            && check_quotes((*tok_tmp).token, token_iter) != '\'')
            {
                //printf("adasdasdasdadasdasdasdadasdasdasdadasdasdasdadasdasdasdadasdasdasd\n");
                expscan_token(msh, tok_tmp);//&(*tok_tmp)
            }
            (tok_tmp)++;
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



//when two expansions in one token joining them did not go well
// printing exp array
// [Hellotest1]
// [test2]
// [==1337066== Invalid read of size 1

// ==1337066== 
// test3#jdksks$VA'kjshhsk']
// [#jdkskstest1]
// [test2]
// [test3'kjshhsk']
// [(nil)]
//may be a problem in concatenation logic
