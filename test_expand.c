/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/27 23:46:36 by wweerasi         ###   ########.fr       */
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

void    get_cur_exp_arr(t_msh *msh, t_expan *exp, char *exp_dup, int q_context)
{
    char *tmp_exp_dup;
    
    if (*exp_dup && q_context)
    {
        tmp_exp_dup = exp_dup;
        while (*tmp_exp_dup)
        {
            if (ft_strchr("\t\n\r\f\v", *tmp_exp_dup))
                *tmp_exp_dup = ' ';
            tmp_exp_dup++;
        }
        exp -> cur_exp_arr = ft_split(exp_dup, ' ');
        free(exp_dup);//see if this is appropriate. in else case we assign it to the array so we need to keep it. but here we have a brand new array. so no need of exp_dup.
    }
    else
    {
        exp -> cur_exp_arr = ft_calloc(2, sizeof(char *));
        if (exp -> cur_exp_arr)
            *(exp -> cur_exp_arr) = exp_dup;
        else
            free(exp_dup); //if array creation failed we will loose exp_dup because it is not in our struct
    }
    if (!exp -> cur_exp_arr)
        exit(printf("# minishell: Error:Malloc Fail.\n"));
}

void    concat_or_extend_exp_edge(t_msh *msh, t_expan *exp, char *exp_val)
{
    int leading_spc;
    int trailing_spc;

    leading_spc = (ft_strchr("\t\n\r\f\v", *exp_val) != NULL);
    trailing_spc = (ft_strchr("\t\n\r\f\v", exp_val[ft_strlen(exp_val) - 1]) != NULL);//check if index is correct
    //what id len is zero? it will make index -1
}

void    expand_parameter(t_msh *msh, t_expan *exp)
{
    char    *exp_val;
    char    *exp_dup;

    exp_val = get_env(msh -> envl, exp -> key);
    if (exp_val)
        exp_dup = ft_strdup(exp_val);
    else
        exp_dup = ft_strdup("");
    if (!exp_dup)
        exit(printf("# minishell: Error:Malloc Fail.\n"));
    get_cur_exp_arr(msh, exp, exp_dup, check_quotes(exp -> exp, exp -> prefix));
    concat_or_extend_exp_edge(msh, exp, exp_val);
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
        ft_memcpy(exp.prefix, exp.suffix, sizeof(char));
        printf("exp.exp: %s\n", exp.exp);
        exp.suffix++;
        exp.prefix++;
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