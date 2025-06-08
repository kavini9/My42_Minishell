/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/07 22:02:33 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char *extract_env_key(char **token)
{
    char *start;
    int var_len;
    
    var_len = 0;
    (*token)++;
    start = *token;
    while (**token && (ft_isalnum(**token) || **token == '_' || **token == '?' || **token == '$'))//added **token && (other cases) for when command line ends with $
    {
        if (var_len == 0 || (**token != '?' && **token != '$'))
        {
            var_len++;
            (*token)++;
        }
        if ((start == *token - 1 && ft_isdigit(*(*token - 1))) 
        || **token == '?' || **token == '$')
            break;
        // if ((start == *token - 1 && ft_isdigit(*(*token - 1))) 
        // || *(*token - 1) == '?' || *(*token - 1) == '$')
        //     break;
    }
    return (ft_substr(start, 0, var_len));
}

void    expand_parameter(t_msh *msh, t_token *token, t_expan *exp)
{
    char    *exp_val;
    char    *exp_dup;
    int q_context;

    q_context = check_quotes(exp -> tok, exp -> suffix);//there's somthing wrong in this. q_context is wrong.//before if was (exp -> exp, exp -> prefix)
    exp_val = extract_exp_value(msh -> envl, exp -> key);//get_env(msh -> envl, exp -> key);//this needs to be replaced to get $? $$
    if (exp_val)
        exp_dup = ft_strdup(exp_val);
    else
        exp_dup = ft_strdup("");
    if (!exp_dup)
        exit(printf("# minishell: expand_parameter: Error:Malloc Fail.\n"));
    get_tmp_arr(msh, exp, exp_dup, q_context);//I hope sending argument like this will prevent it from spliting expand when token is redir type
    adjust_exp_edge(msh, exp, exp_val, q_context);
    revise_exp_arr(msh, token, exp);
}

void expscan_token(t_msh *msh, t_token *token)
{
    t_expan exp;

    init_exp(msh, *token, &exp);
    while (*(exp.suffix))
    {
        //printf("check quotes: %i\n", check_quotes(exp.tok, exp.suffix));//runs in to a infinite loop when the expand is splitted.
        if (*(exp.suffix) == '$' && check_quotes(exp.tok, exp.suffix) != '\'')//why quote condition doesnt work here
        {//do we need suffix + 1. why do I do that in test_parse
            exp.key = extract_env_key(&(exp.suffix));
            if (!exp.key)
                exit(printf("# minishell: expscan_token: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC //  have to free exp.prefix.
            if (*exp.key)//this is for when we have something like $%
                expand_parameter(msh, token, &exp);
            // else
            //     exp.suffix--;//to copy the $ to the string. $ will be incremented after the if condition.
        }
        if (*(exp.suffix) && !(*(exp.suffix) == '$' && check_quotes(exp.tok, exp.suffix) != '\''//what if we add check_quote here. it solved infinite loop, but '$VAR1'$USER doesn't work now.
        && (ft_isalnum(*(exp.suffix + 1)) || *(exp.suffix + 1) == '_' 
        || *(exp.suffix + 1) == '?' || *(exp.suffix + 1) == '$')))// && *exp.key)) //&& *(exp.suffix) != '$')//$$runs this into a infinite 
        {
            ft_memcpy(exp.exp, exp.suffix, sizeof(char));
            exp.suffix++;
            exp.exp++;
        }
    }
}

//need to add another condition to avoid splitting token with redir flags. SECOND: added this inside because it still needs to be expanded
void expand_tokens(t_msh *msh, t_token **token)
{
    char *token_iter;
    t_token *tok_tmp;

    while (*token)
    {
        tok_tmp = *token;
        while ((*tok_tmp).token)//use 
        {
            token_iter = ft_strchr((*tok_tmp).token, '$');
            while (token_iter && *token_iter && check_quotes((**token).token, token_iter) == '\'')//we removed token_iter + 1 in check quotes.
                token_iter = ft_strchr((++token_iter), '$');//this part was added because I checked the availability of the tilde here as well may be we dont need it here just add the condition check quotes in if
            if ((*tok_tmp).redir != REDIR_HDOC && token_iter 
            && check_quotes((*tok_tmp).token, token_iter) != '\'')
                expscan_token(msh, tok_tmp);//&(*tok_tmp)
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