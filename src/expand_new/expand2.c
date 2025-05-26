/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:11:45 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/24 01:28:06 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
void expscan_token(t_msh *msh, t_token token)
{
    t_expan exp;

    
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