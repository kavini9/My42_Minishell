/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/26 21:18:18 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
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
        {
            var_len++;
            (*token)++;
        }
        if ((start == *token && ft_isdigit(**token)) || **token == '?')
            break;
    }
    return (ft_substr(start, 0, var_len));
}

void expscan_token(t_msh *msh, t_token token)
{
    t_expan exp;

    init_exp(msh, token, &exp);
    while (exp.suffix)
    {
        if (*(exp.suffix) == '$' && check_quotes(exp.tok, exp.suffix) != '\'') //do we need siffix + 1. why do I do that in test_parse
            exp.key = extract_env_key(&(exp.suffix));
        if (!exp.key)
            exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC //  have to free exp.prefix.
        else
            printf("key: %s\n exp.suffix: %s\n", exp.key, exp.suffix);
        ft_memcpy(exp.prefix, exp.suffix, sizeof(char));
        exp.suffix++;
        exp.prefix++;
    }
}

void expand_and_setup_cmd(t_msh *msh, t_token **token, t_cmd **cmd)
{
    char *token_iter;

    while (*token)
    {
        while ((**token).token)
        {
            token_iter = ft_strchr("$~", *(**token).token);
            while (*token_iter && check_quotes((**token).token, token_iter + 1) == '\'')
                token_iter = ft_strchr("$~", *(++token_iter) );
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