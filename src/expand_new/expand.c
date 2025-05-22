/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/22 22:40:52 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void init_cmd_struct(t_msh *msh, int cmd_count)
{
    t_cmd **tmp_cmd;
    
    msh -> cmd = ft_calloc(cmd_count + 1, sizeof(t_cmd *));
    if (!msh -> cmd)
		exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
    tmp_cmd = msh -> cmd;
    while (cmd_count--)
    {
        *tmp_cmd = ft_calloc(1, sizeof(t_cmd));
        if (!*tmp_cmd)
             exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
        tmp_cmd++;
    }
}

char *extract_env_key(char **token)
{
    char *start;
    int var_len;
    
    var_len = 0;
    (*token)++;
    start = *token;
    while (!ft_isalnum(**token) || **token == '_')
    {
        var_len++;
        (*token)++;
        if (start == *token && ft_isdigit(**token))
            break;
    }
    return (ft_substr(start, 0, var_len));
}

void    expand_parameter(t_msh *msh,  char *expan, char *token, char *key)
{
    int q_context;
    char    *exp_val;
    int     is_white;

    q_context = check_quotes(expan, NULL);
    exp_val = get_env(msh -> envl, key); //might have to write something to get env and handle digits and pid.
    if (exp_val && !q_context)
    {
        is_white = (ft_strchr(" \t\n\r\f\v", *exp_val) != NULL);
        
    }
        
    
}

void expan_scan_token(t_msh *msh, char *token, t_cmd *cmd)
{
    char *expan;
    char *start;
    char *key;

    start = token;
    expan = ft_calloc(ft_strlen(token), sizeof(char));
    if (!expan)
        exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
    while(*token)
    {
        if (token == '$' && check_quotes(start, token + 1) != '\'' 
        && (ft_isalnum(*(token + 1)) || *(token + 1) == '_'))
        {
            key = extract_env_key(&(token));
            if (!key)
                exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC //  have to free expan
            expand_parameter(msh,  expan, token, key);
        }
        ft_memcpy(expan, token, sizeof(char));
        token++;
        expan++;
    }
}

void expand_and_setup_cmd(t_msh *msh, t_token **token, t_cmd **cmd)
{
    while (*token)
    {
        while ((**token).token)
        {
            expan_scan_token(msh, (**token).token, cmd);
             
        }  
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